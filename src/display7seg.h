/*
 * display7seg.h
 *
 * Created: 8/12/2014 5:39:20 PM
 *  Author: Andrei
 */ 


#ifndef DISPLAY7SEG_H_
#define DISPLAY7SEG_H_

#include <stdio.h>

#define DISPLYSISE 3

void DisplayInitSTD(void);
void DisplayDrv(void);	

char CharTo7Seg(char ch);
char ClearScr();
char BackSpace();

char GoToX(int);

void DisplayBlink(int period);

void DisplayBlinkOff( void );


#endif /* DISPLAY7SEG_H_ */
