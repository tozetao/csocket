#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static short stop = 0;

static void handle_term(int sig)
{
    stop = 1;
}

int main()
{
    // kill命令传递的默认信号，相当于询问当前进程是否要执行关闭
    signal(SIGTERM, handle_term);

    const char ip[] = "192.168.0.136";
    
    int port = 9001;
    int backlog = 5;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 创建IPv4 socket地址
    struct sockaddr_in address;
    bzero(&address, sizeof(address));

    inet_pton(AF_INET, ip, (void *)&address.sin_addr);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    int ret = bind(sockfd, (struct sockaddr*) &address, sizeof(address));
    assert(ret != -1);

    ret = listen(sockfd, backlog);
    assert(ret != -1);

    while (!stop)
        sleep(1);

    close(sockfd);

    return 0;
}

/*
listen(int sockfd, int backlog)
    backlog：指内核监听socket队列的最大长度，在内核2.2版本之前，backlog指处于半连接状态和完全连接状态的socket
    的上线，在2.2版本之后，backlog指完全连接状态的socket数量。
    超过backlog指定的数量，内核将不受理，客户端也会收到一个ECONNREFUSED错误信息。

    一般完整连接最多有backlog+1个，在不同系统可能略有不同。
*/


