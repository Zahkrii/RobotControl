#ifndef __FILEREADER_H__
#define __FILEREADER_H__

extern char cmd[100][119];
extern int fileOpen(const char *fileName);
extern void readCommand(const char *fileName);
#endif