/*****************************************************************************
File name: sensor.c
Description: 使用超声波传感器检测机器人前方是否有障碍
Author: 解东燊
Version: 1.0.1
Date: 2021/11/18
*****************************************************************************/

#include <stdio.h>
#include <wiringPi.h>
#include <sys/time.h>
#include "sensor.h"

#define Trig 0
#define Echo 1

/*************************************************
Function: sensorInit
Description: 初始化引脚模式
*************************************************/
void sensorInit()
{
    // wiringPiSetup();
    pinMode(Trig, OUTPUT);
    pinMode(Echo, INPUT);
}

/*************************************************
Function: getDistance
Description: 获取机器人离前方障碍物的距离
Return: 距离
*************************************************/
float getDistance()
{
    struct timeval tv1;
    struct timeval tv2;
    long start, stop;
    float distance;

    digitalWrite(Trig, LOW);
    delayMicroseconds(2);

    digitalWrite(Trig, HIGH);
    delayMicroseconds(15);
    digitalWrite(Trig, LOW);

    while (!(digitalRead(Echo) == 1))
        ;
    gettimeofday(&tv1, NULL);

    while (!(digitalRead(Echo) == 0))
        ;
    gettimeofday(&tv2, NULL);

    start = tv1.tv_sec * 1000000 + tv1.tv_usec;
    stop = tv2.tv_sec * 1000000 + tv2.tv_usec;

    distance = (float)(stop - start) / 1000000 * 34000 / 2;

    return distance;
}