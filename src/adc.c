/*
 * adc.c
 *
 * Created: 8/14/2014 5:19:37 PM
 *  Author: Andrei
 */ 

#include <avr/io.h>

void ADC_init(void)
{
	ADCSRA=(1<<ADEN)|(0<<ADIE)|(1<<ADSC)|(1<<ADPS2)|(0<<ADPS1)|(0<<ADPS0);
	ADMUX=0;
}

int GetADC(int chanel)
{
	int adcData=-1;
	if(adcData<8)
	{
		ADMUX=(ADMUX&0xf8)+chanel;
		
		ADCSRA|=1<<ADSC;
		
		while(ADCSRA&(1<<ADSC));
		
		adcData=ADCL;
		adcData|=(int)ADCH<<8;
	}
	return adcData;
}
