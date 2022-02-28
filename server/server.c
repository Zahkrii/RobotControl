#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>
#include <strings.h>
#include "server.h"

int server_init(void)
{
    int ser_fd = 0;
    struct sockaddr_in seraddr;

    ser_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (ser_fd == -1)
    {
        perror("socket");
        return 1;
    }
    bzero(&seraddr, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_port = htons(SER_PORT);
    bind(ser_fd, (struct sockaddr *)&seraddr, sizeof(seraddr));

    listen(ser_fd, 128);

    printf("server init ok\r\n");
    return ser_fd;
}

int server_accept(int ser_fd)
{
    int cli_fd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddr_len;
    char clie_ip[BUFSIZ] = {0};

    cliaddr_len = sizeof(cliaddr);
    printf("Waiting APP...\n");
    cli_fd = accept(ser_fd, (struct sockaddr *)&cliaddr, &cliaddr_len);

    printf("Client IP: %s, Client port: %d\n",
           inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, clie_ip, sizeof(clie_ip)),
           ntohs(cliaddr.sin_port));
    return cli_fd;
}

int server_recv(int cli_fd, char *buf, int len)
{
    int n = 0;

    n = read(cli_fd, buf, len);

    return n;
}

void server_close(int ser_fd)
{
    close(ser_fd);
}
