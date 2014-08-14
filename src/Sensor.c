/*
 * Sensor.c
 *
 *  Created on: Aug 14, 2014
 *      Author: Andrei
 */

#include "Sensor.h"
#include "i2cmaster.h"



int Geti2cSensorData(void)
{
	i2c_start_wait(0b10000000+I2C_WRITE);
	i2c_write(0b11110011);
	//_delay_ms(100);
	while(i2c_rep_start(0b10000000+I2C_READ));
	int St = (i2c_readAck()<<8);
	St |= i2c_readAck();
	i2c_readNak();

	i2c_stop();
	int temperature = TemperaturaConversata(St);
	return temperature;
}


int TemperaturaConversata(int St)
{
	float temperatura;
	temperatura = -46.85 + (175.72 * St/65536);
	return (int)(temperatura*10);
}


