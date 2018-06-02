#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1000
void error_handling(char* message);

int main(int argc, char * argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "hello world";

    if(argc!=2)
    {
        printf("usage: %s", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
    {
        error_handling("socket() error\n");
        return -1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handling("bind() error");
        return -1;
    }

    if(listen(serv_sock, 5) == -1)
    {
        error_handling("listen() error");
        return -1;
    }

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*) & clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1)
    {
        error_handling("accept() error");
        return -1;
    }
    
    int content[BUF_SIZE];
    int i;
    read(clnt_sock, content, BUF_SIZE-1);
    for(i = 0; i < 1000000; i++)
        printf("wait time: %d\n", i);
    write(clnt_sock, content, sizeof(content));
    //write(clnt_sock, message, sizeof(message));
    /*
    char msg1[] = " this is your book. ";
    write(clnt_sock, msg1, sizeof(msg1));

    char msg2[] = " tank. ";
    write(clnt_sock, msg2, sizeof(msg2));
    */

    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(char * msg)
{
    printf("%s\n", msg);
}