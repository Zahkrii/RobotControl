/*****************************************************************************
File name: main.c
Description: 主程序代码
Author: 解东燊
Version: 1.0.1
Date: 2021/11/19
*****************************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "server.h"
#include "sensor.h"
#include "angle.h"
#include "filereader.h"
#include "roboaction.h"

int connectFlag;                    //连接状态Flag
pthread_t forwardId, backwardId;    //循环动作线程ID
int server_fd, client_fd, angle_fd; //文件描述符

/*************************************************
Function: ExecuteCommand
Description: 处理收到的指令并执行动作
Param: cmd 指令
*************************************************/
void ExecuteCommand(char cmd)
{
    switch (cmd)
    {
    case 'p':
        //robot standup
        robotAct(stand);
        break;
    case 'w':
        //robot forward start
        if (forwardFlag == 1)
        {
            breakFlag = 0;
            robotAct(forward_start);
            pthread_create(&forwardId, NULL, robotActThread, &forward_loop);
        }
        break;
    case 't':
        //robot forward stop
        breakFlag = 1;
        pthread_join(forwardId, NULL);
        if (forwardFlag == 1)
            robotAct(forward_end);
        break;
    case 'a':
        //robot left
        robotAct(left);
        break;
    case 's':
        //robot backward start
        breakFlag = 0;
        robotAct(backward_start);
        pthread_create(&backwardId, NULL, robotActThread, &backward_loop);
        break;
    case 'g':
        //robot backward stop
        breakFlag = 1;
        pthread_join(backwardId, NULL);
        robotAct(backward_end);
        break;
    case 'd':
        //robot right
        robotAct(right);
        break;
    case '1':
        //robot action 1
        robotAct(act1);
        break;
    case '2':
        //robot action 2
        robotAct(act2);
        break;
    case '3':
        //robot action 3
        robotAct(act3);
        break;
    case '4':
        //robot side stand
        robotAct(side_stand);
        break;
    case '5':
        //robot front stand
        robotAct(front_stand);
        break;
    default:
        break;
    }
}

/*************************************************
Function: serverReceiveThread
Description: 服务器接受数据的线程
*************************************************/
void *serverReceiveThread(void *arg)
{
    char buffer[BUFSIZ];
    int n = 0;
    int clientFlag = *((int *)arg);
    while (1)
    {
        printf("Waiting command...\n");
        n = server_recv(client_fd, buffer, sizeof(buffer));
        write(client_fd, buffer, n);
        if (n == 0)
        {
            connectFlag = 0;
            printf("Connection closed by peer.\n");
            break;
        }
        if (n > 0)
        {
            printf("Received[%c]\r\n", buffer[0]);
            ExecuteCommand(buffer[0]);
        }
    }
}

/*************************************************
Function: main
Description: 主函数
*************************************************/
int main()
{
    float distance;
    int x, y;
    int stat = -1;
    int receiveErr;
    pthread_t receiveId;

    forwardFlag = 1;

    server_fd = server_init();
    if (server_fd < 0)
    {
        printf("Server init failed!\n");
        return -1;
    }
    client_fd = server_accept(server_fd);
    connectFlag = 1;
    printf("client_fd ok, connectFlag: %d\n", connectFlag);

    if (wiringPiSetup() == -1)
    {
        printf("Setup wiringPi failed!\n");
        return -2;
    }

    robotInit();
    sensorInit();
    angle_fd = angleInit();

    receiveErr = pthread_create(&receiveId, NULL, serverReceiveThread, &client_fd);
    if (receiveErr != 0)
    {
        printf("Create thread failed! Details:\n%s", strerror(receiveErr));
    }

    robotAct(stand);

    while (connectFlag)
    {
        distance = getDistance();
        //printf("Distance: %.2f\n", distance);
        if ((int)distance < 8)
        {
            forwardFlag = 0;
            //ExecuteCommand('t');
        }
        else
            forwardFlag = 1;

        /*
        stat = getStat(angle_fd);
        x = angle_data_get(angle_fd, 0);
        x = angle_data_get(angle_fd, 1);
        printf("x=%d, y=%d\n", x, y);
        if (stat == 2 || stat == 3)
        {
            printf("Stand up Executed. Code: %d\n", stat);
            //ExecuteCommand('p');
        }
        */

        delay(1000);
    }

    server_close(client_fd);
    server_close(server_fd);

    return 0;
}