/****************
Name:
Date:
Author:
****************/
#ifndef PID_H
#define PID_H


#ifndef ERR_TAB_SIZE
#define ERR_TAB_SIZE 100
#endif

int	PID_Control(int Va, int Vd);
void PID_SetKp(char K);
void PID_SetKd(char K);
void PID_SetKi(char K);



#endif //PID_H
