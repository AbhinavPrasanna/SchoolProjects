// Asgn 2: A simple HTTP server.
// By: Eugene Chou
//     Andrew Quinn
//     Brian Zhao

#include "asgn2_helper_funcs.h"
#include "connection.h"
#include "debug.h"
#include "response.h"
#include "request.h"
#include "queue.h"

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <pthread.h>

#include <sys/stat.h>

#define VOIDPT2INT(p) (int) (uintptr_t) (p)
#define INT2VOIDPT(i) (void *) (uintptr_t) (i)

void handle_connection(int);

void handle_get(conn_t *);
void handle_put(conn_t *);
void handle_unsupported(conn_t *);

void *consumer_function(void *queue) {
    void *connection;
    while (1) {
        queue_pop(queue, &connection);
        int connection2 = VOIDPT2INT(connection);
        handle_connection(connection2);
        close(connection2);
    }
}

int main(int argc, char **argv) {
    int numthreads = 4;
    const char *port2;
    if (argc < 2) {
        warnx("wrong arguments: %s port_num", argv[0]);
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }
    switch (argc) {
    case 2:
        if (strcmp(argv[1], "-t") == 0) {
            printf("Error: invalid argument '%s'\n", argv[1]);
            return 1;
            break;
        } else {
            port2 = argv[1];
            break;
        }
    case 4:
        if (strcmp(argv[1], "-t") == 0) {
            numthreads = atoi(argv[2]);
            port2 = argv[3];
            break;
        } else {
            printf("Error: invalid argument '%s'\n", argv[1]);
            return 1;
            break;
        }
    default: printf("Error: invalid number of arguments\n"); return 1;
    }

    char *endptr = NULL;
    size_t port = (size_t) strtoull(port2, &endptr, 10);
    if (endptr && *endptr != '\0') {
        warnx("invalid port number: %s", port2);
        return EXIT_FAILURE;
    }
    queue_t *queue = queue_new(numthreads);
    if (queue == NULL) {
        fprintf(stderr, "queue_new failed\n");
    }
    pthread_t *threads = malloc(sizeof(pthread_t) * numthreads);
    for (int i = 0; i < numthreads; i++) {
        pthread_create(&threads[i], NULL, &consumer_function, queue);
    }

    signal(SIGPIPE, SIG_IGN);
    Listener_Socket sock;
    listener_init(&sock, port);

    while (1) {
        int connfd = listener_accept(&sock);
        if (connfd < 0) {
            break;
        }
        queue_push(queue, INT2VOIDPT(connfd));
    }
    queue_delete(&queue);
    return EXIT_SUCCESS;
}

void handle_connection(int connfd) {

    conn_t *conn = conn_new(connfd);

    const Response_t *res = conn_parse(conn);

    if (res != NULL) {
        conn_send_response(conn, res);
    } else {
        //debug("%s", conn_str(conn));
        const Request_t *req = conn_get_request(conn);
        if (req == &REQUEST_GET) {
            handle_get(conn);
        } else if (req == &REQUEST_PUT) {
            handle_put(conn);
        } else {
            handle_unsupported(conn);
        }
    }

    conn_delete(&conn);
}

void handle_get(conn_t *conn) {

    char *uri = conn_get_uri(conn);
    const Response_t *res = NULL;
    //debug("GET request not implemented. But, we want to get %s", uri);
    int fd = open(uri, O_RDONLY);
    if (fd < 0) {
        switch (errno) {
        case EACCES: conn_send_response(conn, &RESPONSE_FORBIDDEN); break;
        case ENOENT: conn_send_response(conn, &RESPONSE_NOT_FOUND); break;
        default: conn_send_response(conn, &RESPONSE_INTERNAL_SERVER_ERROR); break;
        }
        fprintf(stderr, "GET,%s,%d,%s\n", uri, response_get_code(res),
            conn_get_header(conn, "Request-Id"));
        close(fd);
        return;
    } else {
        struct stat st;
        fstat(fd, &st);
        if (S_ISDIR(st.st_mode)) {
            conn_send_response(conn, &RESPONSE_FORBIDDEN);
            fprintf(stderr, "GET,%s,%d,%s\n", uri, response_get_code(res),
                conn_get_header(conn, "Request-Id"));
            close(fd);
            return;
        }
        flock(fd, LOCK_SH);
        conn_send_file(conn, fd, st.st_size);
        flock(fd, LOCK_UN);
        if (res == NULL) {
            res = &RESPONSE_OK;
        }
        fprintf(stderr, "GET,%s,%d,%s\n", uri, response_get_code(res),
            conn_get_header(conn, "Request-Id"));
        close(fd);
    }
    // What are the steps in here?

    // 1. Open the file.
    // If  open it returns < 0, then use the result appropriately
    //   a. Cannot access -- use RESPONSE_FORBIDDEN
    //   b. Cannot find the file -- use RESPONSE_NOT_FOUND
    //   c. other error? -- use RESPONSE_INTERNAL_SERVER_ERROR
    // (hint: check errno for these cases)!

    // 2. Get the size of the file.
    // (hint: checkout the function fstat)!

    // Get the size of the file.

    // 3. Check if the file is a directory, because directories *will*
    // open, but are not valid.
    // (hint: checkout the macro "S_IFDIR", which you can use after you call fstat!)

    // 4. Send the file
    // (hint: checkout the conn_send_file function!)
}

void handle_unsupported(conn_t *conn) {
    //debug("handling unsupported request");

    // send responses
    conn_send_response(conn, &RESPONSE_NOT_IMPLEMENTED);
}

void handle_put(conn_t *conn) {

    char *uri = conn_get_uri(conn);
    const Response_t *res = NULL;
    //debug("handling put request for %s", uri);

    // Check if file already exists before opening it.
    bool existed = access(uri, F_OK) == 0;
    //debug("%s existed? %d", uri, existed);

    // Open the file..
    int fd = open(uri, O_CREAT | O_TRUNC | O_WRONLY, 0600);
    if (fd < 0) {
        //debug("%s: %d", uri, errno);
        if (errno == EACCES || errno == EISDIR || errno == ENOENT) {
            res = &RESPONSE_FORBIDDEN;
            goto out;
        } else {
            res = &RESPONSE_INTERNAL_SERVER_ERROR;
            goto out;
        }
    }
    flock(fd, LOCK_EX);
    res = conn_recv_file(conn, fd);
    flock(fd, LOCK_UN);
    if (res == NULL && existed) {
        res = &RESPONSE_OK;
    } else if (res == NULL && !existed) {
        res = &RESPONSE_CREATED;
    }

    close(fd);

out:
    conn_send_response(conn, res);
    fprintf(
        stderr, "PUT,%s,%d,%s\n", uri, response_get_code(res), conn_get_header(conn, "Request-Id"));
}
