#ifndef __ROBOACTION_H__
#define __ROBOACTION_H__

typedef struct Action
{
    int start;
    int end;
    int count;
} action;

extern action stand;
extern action forward_start;
extern action forward_loop;
extern action forward_end;
extern action right;
extern action left;
extern action act1;
extern action act2;
extern action act3;
extern action backward_start;
extern action backward_loop;
extern action backward_end;
extern action side_stand;
extern action front_stand;

extern int serial;
extern int breakFlag;
extern int forwardFlag;

extern void robotAct(action act);
extern void *robotActThread(void *arg);
extern void robotInit();
#endif