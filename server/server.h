#ifndef __SERVER_H__
#define __SERVER_H__

#define SER_IP "192.168.12.1"
#define SER_PORT 5647

extern int server_init(void);
extern int server_accept(int ser_fd);
extern int server_recv(int cli_fd, char *buf, int len);
extern void server_close(int ser_fd);
#endif
