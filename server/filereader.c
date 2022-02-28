/*****************************************************************************
File name: filereader.c
Description: 用于读取机器人动作指令
Author: 解东燊
Version: 1.0.1
Date: 2021/11/18
*****************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "filereader.h"

char cmd[100][119];

/*************************************************
Function: fileOpen
Description: 打开文件
Param: *fileName 文件完整目录地址
Return: 文件描述符，-1 表示出错
*************************************************/
int fileOpen(const char *fileName)
{
    int fd = open(fileName, O_RDONLY);
    if (fd < 0)
    {
        perror("Open file Error! Details:\n");
        return -1;
    }
    return fd;
}

/*************************************************
Function: readCommand
Description: 从文件读取机器人动作指令，存储到cmd数组并打印到控制台
Param: *fileName 文件完整目录地址
*************************************************/
void readCommand(const char *fileName)
{
    int fd = fileOpen(fileName);
    char *locate = NULL;
    char buffer[1024 * 10] = {0};
    read(fd, buffer, sizeof(buffer));
    locate = strstr(buffer, "G0000");

    for (int i = 0; i < 62; i++)
    {
        memcpy(cmd[i], locate, 103); //存储到cmd数组
        locate += 104;
        printf("#%d: %s\n", i, cmd[i]); //打印完整动作指令列表
    }
}