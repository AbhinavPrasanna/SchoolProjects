#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <regex.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include "asgn2_helper_funcs.h"

#define BUFSIZE            1024
#define MAX_REQUEST_LENGTH 2048
#define Header_Fields      128
#define REGEX              "^([a-zA-Z]{0,8}) /([a-zA-Z0-9._-]{2,64}) HTTP/([0-9]).([0-9])\r\n"
#define REGEX2             "^([a-zA-Z]{0,8}) /([a-zA-Z0-9._-]{2,64}) HTTP/([0-9]).([0-9])(\r\n)?"
#define REGEX3             "([a-zA-Z0-9.-]+): ([0-9]+)(\r\n\r\n)?"
#define CONTENT            1000000
void get(int accept, char *buffer, regmatch_t matches[]) {
    struct stat file_info;
    char *response = calloc(MAX_REQUEST_LENGTH, sizeof(char));
    char *uri = strndup(buffer + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);

    char *version1 = strndup(buffer + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
    char *version2 = strndup(buffer + matches[4].rm_so, matches[4].rm_eo - matches[4].rm_so);
    if (strcmp(version1, "1") != 0 || strcmp(version2, "1") != 0) {
        sprintf(response, "HTTP/1.1 505 Version Not Supported\r\nContent-Length: 22\r\n\r\nVersion "
                          "Not Supported\n");
        write(accept, response, strlen(response));
        free(response);
        free(uri);
        free(version1);
        free(version2);
        close(accept);
        return;
    }
    if (uri == NULL || access(uri, F_OK) == -1) {
        sprintf(response, "HTTP/1.1 404 Not Found\r\nContent Length: 10\r\n\r\nNot Found\n");
        write_all(accept, response, strlen(response));
        free(response);
        free(uri);
        free(version1);
        free(version2);
        close(accept);
        return;
    }
    stat(uri, &file_info);
    int fd = 0;
    if ((fd = open(uri, O_RDONLY)) > -1) {
        if (S_ISDIR(file_info.st_mode)) {
            sprintf(response, "HTTP/1.1 403 Forbidden\r\nContent Length: 10\r\n\r\nForbidden\n");
            write_all(accept, response, strlen(response));
            free(response);
            free(uri);
            free(version1);
            free(version2);
            close(fd);
            close(accept);
            return;
        }
    }
    if (fd == -1) {
        sprintf(response, "HTTP/1.1 403 Forbidden\r\nContent Length: 10\r\n\r\nForbidden\n");
        write_all(accept, response, strlen(response));
        close(accept);
        return;
    }
    sprintf(response, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n", file_info.st_size);
    write_all(accept, response, strlen(response));
    pass_bytes(fd, accept, file_info.st_size);
    free(response);
    free(uri);
    free(version1);
    free(version2);
    close(fd);
    close(accept);
}
void put(int accept, char *buffer, regmatch_t matches[]) {
    regex_t regex3;
    regmatch_t matches2[4];
    struct stat file_info;
    char *response = calloc(MAX_REQUEST_LENGTH, sizeof(char));
    char *uri = strndup(buffer + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
    char *version1 = strndup(buffer + matches[3].rm_so, matches[3].rm_eo - matches[3].rm_so);
    char *version2 = strndup(buffer + matches[4].rm_so, matches[4].rm_eo - matches[4].rm_so);
    char *extracontent = strndup(buffer + matches[4].rm_eo, strlen(buffer) - matches[4].rm_eo);
    int reg = regcomp(&regex3, REGEX3, REG_EXTENDED);
    if (reg == -1) {
        fprintf(stderr, "Could not compile regex\n");
    }
    int exec = regexec(&regex3, extracontent, 4, matches2, 0);
    if (exec == -1) {
        fprintf(stderr, "Could not execute regex\n");
    }
    long contentlength = strtol(
        strndup(extracontent + matches2[2].rm_so, matches2[2].rm_eo - matches2[2].rm_so), NULL, 10);
    if (strcmp(version1, "1") != 0 || strcmp(version2, "1") != 0) {
        sprintf(response, "HTTP/1.1 505 Version Not Supported\r\nContent-Length: 22\r\n\r\nVersion "
                          "Not Supported\n");
        write(accept, response, strlen(response));
        free(response);
        free(uri);
        free(version1);
        free(version2);
        free(extracontent);
        close(accept);
        return;
    }
    int fd = 0;
    stat(uri, &file_info);
    int code = 201;
    if (access(uri, F_OK) == -1) {
        fd = open(uri, O_WRONLY | O_TRUNC, 0666);
        code = 200;
    } else {
        fd = open(uri, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    }
    if (fd > 0 && S_ISDIR(file_info.st_mode)) {
        sprintf(response, "HTTP/1.1 403\r\nContent Length: 10\r\n\r\nForbidden\n");
        write_all(accept, response, strlen(response));
        free(response);
        free(uri);
        free(version1);
        free(version2);
        free(extracontent);
        close(accept);
        return;
    }
    ssize_t bytes_written = pass_bytes(accept, fd, contentlength);
    sprintf(response, "HTTP/1.1 %d %s\r\nContent-Length: %lu\r\n\r\nCreated\r\n\r\n", code,
        "Created", bytes_written);
    bytes_written = write_all(accept, response, strlen(response));
    if (bytes_written == -1) {
        fprintf(stderr, "Error writting from connection: %d", accept);
    }
    free(response);
    free(uri);
    free(version1);
    free(version2);
    free(extracontent);
    close(fd);
    close(accept);
}
int main(int argc, char *argv[]) {
    Listener_Socket socket;
    regex_t regex, regex2;
    char *buffer = calloc(MAX_REQUEST_LENGTH, sizeof(char));
    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    int port = atoi(argv[1]);
    if (port < 1 || port > 65525) {
        fprintf(stderr, "Invalid Port\n");
        exit(1);
    }
    int listen = listener_init(&socket, port);
    int regulate = regcomp(&regex, REGEX, REG_EXTENDED);
    int regulate2 = regcomp(&regex2, REGEX2, REG_EXTENDED);
    if (listen > 0) {
        fprintf(stderr, "Error creating the socket\n");
        regfree(&regex);
        exit(1);
    }
    if (regulate != 0) {
        printf("Error creating regex\n");
        regfree(&regex);
        exit(1);
    }
    if (regulate2 != 0) {
        printf("Error creating regex\n");
        regfree(&regex);
        exit(1);
    }
    while (1) {
        regmatch_t matches[5];
        regmatch_t matches2[7];
        int accept = listener_accept(&socket);
        if (accept == -1) {
            fprintf(stderr, "Error accepting the connection\n");
            exit(1);
        }
        read_until(accept, buffer, MAX_REQUEST_LENGTH, "\r\n\r\n");
        if (strncmp(buffer, "GET", 3) == 0) {
            int exec = regexec(&regex, buffer, 5, matches, 0);
            if (exec != 0) {
                char *response = calloc(2048, sizeof(char));
                sprintf(response,
                    "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n");
                write_all(accept, response, strlen(response));
                close(accept);
            } else {
                get(accept, buffer, matches);
            }
        } else if (strncmp(buffer, "PUT", 3) == 0) {
            int exec = regexec(&regex, buffer, 7, matches2, 0);
            if (exec != 0) {
                char *response = calloc(2048, sizeof(char));
                sprintf(response,
                    "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n");
                write_all(accept, response, strlen(response));
                close(accept);
            }
            put(accept, buffer, matches2);

        } else {
            char *response = calloc(MAX_REQUEST_LENGTH, sizeof(char));
            sprintf(response, "HTTP/1.1 501 Not Implemented\r\nContent-Length: 16\r\n\r\nNot "
                              "Implemented\n");
            write(accept, response, strlen(response));
            close(accept);
        }
    }

    return 0;
}
