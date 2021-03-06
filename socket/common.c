#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <malloc.h>

#define SA struct sockaddr
#define MAXLINE 1024
#define SERVE_PORT 9001

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
