#include "pid.h"

volatile int Kp = 0;
volatile int Kd = 0;
volatile int Ki = 0;

volatile int errTab[ERR_TAB_SIZE];		//Aici vom pastra istoricul erorilor

//**********************************************
//*** Setarea coeficientilor:

void PID_SetKp(char K) {
	Kp = K;
}

void PID_SetKd(char K) {
	Kd = K;
}

void PID_SetKi(char K) {
	Ki = K;
}
//**********************************************

int PID_Control(int Va, int Vd) {
	int e, Vp, Vdif, Vi;
	int errSum = 0;
	static int Vold, errPos;
	int i = 0;
	int Vout;

	e = Vd - Va;
	Vp = Kp * e;

	Vdif = Kd * (Va - Vold);
	Vold = Va;

	if (++errPos >= ERR_TAB_SIZE)
		errPos = 0;

	errTab[errPos] = e;

	// calculam suma erorii
	for (i = 0; i < ERR_TAB_SIZE; i++)
		errSum += errTab[i];

	Vi = Ki * errSum;

	Vout = Vp + Vdif + Vi;

	return Vout;
}
