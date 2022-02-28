/*****************************************************************************
File name: angle.c
Description: 用于检测机器人状态（站立，前倒，后倒）
Author: 解东燊
Version: 1.0.1
Date: 2021/11/18
*****************************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "angle.h"

//模块地址
#define SlaveAddress 0x48

/*************************************************
Function: angleInit
Description: 初始化模块相关功能
Return: 文件描述符，-1 表示出错
*************************************************/
int angleInit()
{
  int fd = -1;
  fd = wiringPiI2CSetup(SlaveAddress);
  if (fd < 0)
  {
    printf("I2C_Setup fail!\r\n");
    return -1;
  }
  else
    return fd;
}

/*************************************************
Function: angle_data_get
Description: 获取xyz角度值
Param: fd wiringPiI2CSetup(SlaveAddress)
Param: chn 选择获取角度的xyz
Return: 角度值，-1 表示出错
*************************************************/
int angle_data_get(int fd, int chn)
{
  if (chn == 0)
  {
    wiringPiI2CWriteReg8(fd, 0x40, 0x00);
    return wiringPiI2CReadReg8(fd, 0x40);
  }
  else if (chn == 1)
  {
    wiringPiI2CWriteReg8(fd, 0x41, 0x00);
    return wiringPiI2CReadReg8(fd, 0x41);
  }
  else if (chn == 2)
  {
    wiringPiI2CWriteReg8(fd, 0x42, 0x00);
    return wiringPiI2CReadReg8(fd, 0x42);
  }
  return -1;
}

/*************************************************
Function: getStat
Description: 获取机器人状态（站立，前倒，后倒）
Param: fd 文件描述符
Return: 机器人状态，1 表示站立状态，2 表示前倒，3 表示后倒，-1 表示出错
*************************************************/
int getStat(int fd)
{
  int x, y;
  x = angle_data_get(fd, 0);
  y = angle_data_get(fd, 1);
  if ((x >= 65 && x <= 66) && (y <= 169 && y >= 170))
    return 1; //站定状态
  else if ((x >= 62 && x <= 63) && (y <= 165 && y >= 166))
    return 2; //前倒状态
  else if ((x >= 63 && x <= 64) && (y <= 167 && y >= 168))
    return 3; //后倒状态
}