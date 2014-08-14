/*
 * display7seg.c
 *
 * Created: 8/12/2014 5:39:04 PM
 *  Author: Andrei
 */ 

#include "display7seg.h"

#include <avr/io.h>


char displaytab[DISPLYSISE]="---";
int displaypos=0;
int cursor =0;


unsigned int blinkPeriod = 0;
unsigned int blinkCounter = 0;



static char DisplayPutChar(char ch);
// legarea putchar de STDIO, casa putem folosi printf
static FILE mystdio = FDEV_SETUP_STREAM(DisplayPutChar,NULL,_FDEV_SETUP_WRITE);

//-----------------------------------------------------------------------------
// Display Driver
//-----------------------------------------------------------------------------


void DisplayInitSTD(void){
		stdout= stdin = &mystdio;
}

void DisplayDrv()
{
	//incr poz
	if(++displaypos>=DISPLYSISE)
	displaypos=0;
	
	//stinge dis
	PORTD = 0;
	
	char ch=displaytab[displaypos];

	PORTB=CharTo7Seg(ch);

	if(displaypos == 1)
		PORTB|=0x01;

	if(++blinkCounter > blinkPeriod )
		blinkCounter = 0;

	if(blinkCounter >= blinkPeriod/2)
		PORTD = 1 << (displaypos + 5);
}

void DisplayBlink(int period){
	blinkPeriod = period;
}

void DisplayBlinkOff(void){
	blinkPeriod = 0;
}


char CharTo7Seg(char ch)
{

	switch(ch)
	{
		case '0':return  0b11101110;
		case '1':return  0b01001000;
		case '2':return  0b11110010;
		case '3':return  0b10110110;
		case '4':return  0b00111100;
		case '5':return  0b10011110;
		case '6':return  0b11011110;
		case '7':return  0b00100110;
		case '8':return  0b11111110;
		case '9':return  0b10111110;
		case '-':return  0b00010000;
		case 'A':return  0b01111111;
		case 'C':return  0b11001010;
		case 'E':return  0b11011010;
		case 'L':return  0b11001000;
		case 'H':return  0b01111100;
		case '.':return  0b00000001;
		default:return 0;
	}

}

static char DisplayPutChar(char ch)
{
	
	if(cursor<DISPLYSISE)
	{
		displaytab[cursor]=ch;
		cursor++;
	}
	return cursor;
}

char ClearScr()
{
	for(int i=0;i<DISPLYSISE;i++)
	{
		displaytab[i]=0;
	}
	return cursor=0;
}

char GoToX(int pos){
	if (pos < DISPLYSISE){
		cursor=pos;
		
	}
	return cursor;
}

//-----------------------------------------------------------------------------

