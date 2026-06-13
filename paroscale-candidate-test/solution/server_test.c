#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<stdint.h>
#include<ctype.h>

//we have to define the configuration

#define PORT		8080
#define BACKLOG 	256
#define MAX_MSG_LEN 	8192
#define HASH_BUCKETS 	4096
#define MAX_DEPS	512
#define PKG_NAME_MAX	256

//we have to give responses to client

#define RESP_OK	   "OK\n"
#define RESP_FAIL  "FAIL\n"
#define RESP_ERROR "ERROR\n"

//The index part

typedef struct pkg_entry{

	char name[PKG_NAME_MAX];
	char deps[MAX_DEPS][PKG_NAME_MAX];
	int ndeps;
	char rdeps[MAX_DEPS][PKG_NAME_MAX];
	int nrdeps;
	struct pkg_entry *next;

} pkg_entry_t;

static pkg_entry_t *hash_table[HASH_BUCKETS];
static pthread_rwlock_t index_lock  = PTHREAD_RWLOCK_INITIALIZER;

//The hash funtion

static uint32_t fnv1a(const char *s)
{
	uint32_t h = 0x811c9dc5u;

	while(*s)
	{
		h ^= (uint8_t)*s++;
		h *= 0x01000193u;
	}
	return h;
}

static inline uint32_t bucket(const char *name)
{
	return fnv1a(name) & (HASH_BUCKETS - 1);
}

static pkg_entry_t *index_find(const char *name)
{
	uint32_t b = bucket(name);

	for(pkg_entry_t *e = hash_table[b]; e; e = e->next){

		if(strcmp (e->name, name) == 0){

			return e;
		}
	}
	return NULL;
}

static void rdep_remove(pkg_entry_t *pkg, const char *dep_name)
{
    for (int i = 0; i < pkg->nrdeps; i++) {

        if (strcmp(pkg->rdeps[i], dep_name) == 0) {
          
            if (i < pkg->nrdeps - 1)

                memcpy(pkg->rdeps[i], pkg->rdeps[pkg->nrdeps - 1], PKG_NAME_MAX);

            pkg->nrdeps--;

            return;
        }
    }
}

static int rdep_add(pkg_entry_t *pkg, const char *dep_name)
{
    for (int i = 0; i < pkg->nrdeps; i++)

        if (strcmp(pkg->rdeps[i], dep_name) == 0)

            return 0;

    if (pkg->nrdeps >= MAX_DEPS)
	
	return -1;

    strncpy(pkg->rdeps[pkg->nrdeps++], dep_name, PKG_NAME_MAX - 1);

    return 0;
}

static pkg_entry_t *index_insert_empty(const char *name)
{
     pkg_entry_t *e = calloc(1, sizeof *e);

	 if (!e) return NULL;

		strncpy(e->name, name, PKG_NAME_MAX - 1);

    		uint32_t b = bucket(name);

    		e->next = hash_table[b];

    		hash_table[b] = e;

    return e;
}

//now we have ti performe command handler part

static const char *cmd_index(const char *pkg_name, char deps[][PKG_NAME_MAX], int ndeps)
{
    pthread_rwlock_wrlock(&index_lock);

    for (int i = 0; i < ndeps; i++) {

        if (!index_find(deps[i])) {

            pthread_rwlock_unlock(&index_lock);
	    return RESP_FAIL;
        }
    }

    pkg_entry_t *e = index_find(pkg_name);

    if (!e) {

        e = index_insert_empty(pkg_name);

        if (!e) {

            pthread_rwlock_unlock(&index_lock);
	    return RESP_ERROR;
        }

    } else {
      
        for (int i = 0; i < e->ndeps; i++) {

            pkg_entry_t *old_dep = index_find(e->deps[i]);

            if (old_dep)

                rdep_remove(old_dep, pkg_name);
        }

        e->ndeps = 0;
    }

     for (int i = 0; i < ndeps; i++) {
        
	size_t dlen = strlen(deps[i]);
        
	 if (dlen >= PKG_NAME_MAX) dlen = PKG_NAME_MAX - 1;
        
	    memcpy(e->deps[e->ndeps], deps[i], dlen);
        
	    e->deps[e->ndeps][dlen] = '\0';
        
	    e->ndeps++;
        
	   pkg_entry_t *dep_entry = index_find(deps[i]);
        
	   if (dep_entry)

               rdep_add(dep_entry, pkg_name);
    }

    
	pthread_rwlock_unlock(&index_lock);
    	return RESP_OK;
}

static const char *cmd_remove(const char *pkg_name)
{
    pthread_rwlock_wrlock(&index_lock);

    pkg_entry_t *e = index_find(pkg_name);

    if (!e) {

        pthread_rwlock_unlock(&index_lock);
        return RESP_OK;
    }

    if (e->nrdeps > 0) {
        
	pthread_rwlock_unlock(&index_lock);
        return RESP_FAIL;
    }

    for (int i = 0; i < e->ndeps; i++) {

        pkg_entry_t *dep = index_find(e->deps[i]);

          if (dep)

            rdep_remove(dep, pkg_name);
    }

    uint32_t b = bucket(pkg_name);

    pkg_entry_t **pp = &hash_table[b];

    while (*pp && *pp != e)

        pp = &(*pp)->next;

    if (*pp)

        *pp = e->next;

    free(e);
    pthread_rwlock_unlock(&index_lock);
    return RESP_OK;
}

static const char *cmd_query(const char *pkg_name)
{
    pthread_rwlock_rdlock(&index_lock);

    pkg_entry_t *e = index_find(pkg_name);

    pthread_rwlock_unlock(&index_lock);

    return e ? RESP_OK : RESP_FAIL;
}

//parser we use message parser to split


static void strip_newline(char *buf)
{
    size_t n = strlen(buf);

    if (n > 0 && buf[n-1] == '\n') buf[--n] = '\0';
    if (n > 0 && buf[n-1] == '\r') buf[--n] = '\0';
}

static int valid_pkg_name(const char *s)
{
    if (!s || !*s) return 0;

    for (const char *p = s; *p; p++) {

        if (*p == '|' || *p == ',' || !isprint((unsigned char)*p))
            return 0;
    }
    return 1;
}

static const char *handle_message(char *line)
{
    strip_newline(line);

    char *cmd  = line;

    char *pipe1 = strchr(cmd, '|');

   	 if (!pipe1) return RESP_ERROR;

   		*pipe1 = '\0';
    
		char *pkg  = pipe1 + 1;

    		char *pipe2 = strchr(pkg, '|');

    	   if (!pipe2) return RESP_ERROR;
    
		*pipe2 = '\0';
    
		char *dep_str = pipe2 + 1;

    int is_index  = strcmp(cmd, "INDEX")  == 0;
    int is_remove = strcmp(cmd, "REMOVE") == 0;
    int is_query  = strcmp(cmd, "QUERY")  == 0;

    if (!is_index && !is_remove && !is_query)
        return RESP_ERROR;

    if (!valid_pkg_name(pkg))
        return RESP_ERROR;

    char deps[MAX_DEPS][PKG_NAME_MAX];
    int  ndeps = 0;

    if (*dep_str) {

        char buf[MAX_MSG_LEN];

        strncpy(buf, dep_str, sizeof buf - 1);

        buf[sizeof buf - 1] = '\0';

        char *tok = strtok(buf, ",");

        while (tok) {

            if (!valid_pkg_name(tok)) return RESP_ERROR;

            if (ndeps >= MAX_DEPS)    return RESP_ERROR;

            strncpy(deps[ndeps++], tok, PKG_NAME_MAX - 1);

            tok = strtok(NULL, ",");
        }
    }
    
	if (is_index)  return cmd_index(pkg, deps, ndeps);
    
		if (is_remove) return cmd_remove(pkg);
    
	return cmd_query(pkg);
}


//we are using threads for the client handling purpse


typedef struct {
    int fd;
} client_ctx_t;

static void *client_thread(void *arg)
{
    client_ctx_t *ctx = (client_ctx_t *)arg;

    int fd = ctx->fd;
    free(ctx);

    pthread_detach(pthread_self());

    char buf[MAX_MSG_LEN];
    size_t buf_used = 0;

    while (1) {

        ssize_t n = recv(fd, buf + buf_used, sizeof buf - buf_used - 1, 0);
        
	if (n <= 0) break;
        
	buf_used += (size_t)n;
        
	buf[buf_used] = '\0';

        char *start = buf;
        char *nl;

        while ((nl = memchr(start, '\n', (size_t)(buf + buf_used - start))) != NULL) {

            *nl = '\0';

            char line[MAX_MSG_LEN];

            size_t len = (size_t)(nl - start);

            if (len >= MAX_MSG_LEN - 1) {

                const char *resp = RESP_ERROR;

                send(fd, resp, strlen(resp), MSG_NOSIGNAL);

            } else {

                memcpy(line, start, len);

                line[len] = '\n';
                line[len + 1] = '\0';

                const char *resp = handle_message(line);

                send(fd, resp, strlen(resp), MSG_NOSIGNAL);
            }

            start = nl + 1;
        }

	buf_used = (size_t)(buf + buf_used - start);

        if (buf_used > 0 && start != buf)

            memmove(buf, start, buf_used);

        if (buf_used == sizeof buf - 1) {

            send(fd, RESP_ERROR, strlen(RESP_ERROR), MSG_NOSIGNAL);
            buf_used = 0;
        }
    }

    close(fd);
    return NULL;
}

//This is the main function 

int main(void)
{
    
    signal(SIGPIPE, SIG_IGN);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) { perror("socket"); return 1; }

    int opt = 1;

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);

    struct sockaddr_in addr = {
        .sin_family      = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port        = htons(PORT),
    };

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof addr) < 0) 
	{
        	perror("bind"); return 1;
    	}

    if (listen(server_fd, BACKLOG) < 0) 
	{
        	perror("listen"); return 1;
    	}

    fprintf(stderr, "[server] Listening on port %d\n", PORT);

    while (1) {

        struct sockaddr_in client_addr;

        socklen_t addrlen = sizeof client_addr;

        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addrlen);

        if (client_fd < 0) 
	{
            if (errno == EINTR) continue;

            perror("accept");
            continue;
        }

        client_ctx_t *ctx = malloc(sizeof *ctx);

        if (!ctx) 
	{
            close(client_fd);
            continue;
        }

        ctx->fd = client_fd;

        pthread_t tid;

	if (pthread_create(&tid, NULL, client_thread, ctx) != 0) 
	{
            perror("pthread_create");
            free(ctx);
            close(client_fd);
        }
    }

    close(server_fd);
    return 0;
}
