#ifndef __ANGLE_H__
#define __ANGLE_H__

#define SlaveAddress 0x48

extern int angleInit();
extern int angle_data_get(int fd, int chn);
extern int getStat();
#endif