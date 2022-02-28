/*****************************************************************************
File name: roboaction.c
Description: 用于执行机器人动作指令
Author: 解东燊
Version: 1.0.1
Date: 2021/11/19
*****************************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <pthread.h>
#include <sys/time.h>
#include "filereader.h"
#include "roboaction.h"

int serial;      //serial文件描述符
int breakFlag;   //中断Flag
int forwardFlag; //前进状态Flag

//包装好的动作结构体，结构体内数据依次为 start 开始动作指令序号，end 开始动作指令序号，count 执行次数
action stand = {0, 0, 1};
action forward_start = {1, 1, 1};
action forward_loop = {2, 7, 10};
action forward_end = {8, 9, 1};
action right = {10, 13, 3};
action left = {14, 17, 3};
action act1 = {18, 29, 1};
action act2 = {30, 34, 1};
action act3 = {35, 43, 1};
action backward_start = {44, 44, 1};
action backward_loop = {45, 50, 10};
action backward_end = {51, 52, 1};
action side_stand = {53, 56, 1};
action front_stand = {57, 61, 1};

/*************************************************
Function: robotAct
Description: 执行动作
Param: act 动作结构体
*************************************************/
void robotAct(action act)
{
    int cnt = act.count;
    while (cnt--)
    {
        for (int i = act.start; i <= act.end; i++)
        {
            serialPrintf(serial, cmd[i]);
            delay(1000);
        }
    }
}

/*************************************************
Function: *robotActThread
Description: 执行循环动作
Param: *arg 传递参数，动作结构体
*************************************************/
void *robotActThread(void *arg)
{
    action act = *((action *)arg);
    int cnt = act.count;
    while (cnt--)
    {
        for (int i = act.start; i <= act.end; i++)
        {
            if (!forwardFlag)
            {
                serialPrintf(serial, cmd[0]);
                pthread_exit(NULL);
                break;
            }
            serialPrintf(serial, cmd[i]);
            delay(1000);
        }
        if (breakFlag)
        {
            pthread_exit(NULL);
            break;
        }
    }
}

/*************************************************
Function: robotInit
Description: 初始化机器人动作相关
*************************************************/
void robotInit()
{
    serial = -1;
    breakFlag = 0;
    readCommand("./robot.ini");
    serial = serialOpen("/dev/ttyAMA0", 115200);
    if (serial < 0)
    {
        printf("Open serial fail!\n");
    }
}