#include <avr/io.h>

#include <avr/interrupt.h> 
#include <avr/wdt.h>

#include "display7seg.h"
#include "Sensor.h"
#include "adc.h"



#define TCNTInit 100

#define T_MAX        700
#define T_MIN        200
#define T_RANGE      (T_MAX-T_MIN)
#define ADC_MAX      1024
#define ADC_CH_BRUT  1
#define ADC_CH_FIN   2

int temperaturaCurenta = 0;
int temperaturaSetata = 0;


#define CNT_1_PERIOD 100	
#define CNT_2_PERIOD 5000

#define SW_PIN 3


void SysTick_Handler(void);
void Delay(uint32_t nTime);

void T0Init()
{
	TIMSK = 1<<TOIE0;
	TCCR0 = 0<<CS02|1<<CS01|0<<CS00;
	TCNT0 = TCNTInit;
}

int cnt = 0;
	
ISR(TIMER0_OVF_vect)
{

	TCNT0=TCNTInit;
	SysTick_Handler();
	// driver Afisare
	DisplayDrv();	


//	control 100 ms

		//.....

	
}

volatile uint32_t TimingDelay;

void Delay(uint32_t nTime){
	TimingDelay = nTime;
	while(TimingDelay != 0);
}

void SysTick_Handler(void) {
	if (TimingDelay != 0x00)
		TimingDelay--;
}


int err[10];

#define IsControlMode() ((PIND & 1 << SW_PIN)!=0)

int main(void)
{

	wdt_disable();
	int cnt_get_i2c = 0;
	int cnt_get_adc = CNT_1_PERIOD/2;
	int cnt_switch = CNT_1_PERIOD/4;



	PORTB = 0x00;
	DDRB  = 0xff;
	PORTC = 0xFF &(~ (1<<PC1)|(1<<PC2));
 	DDRC  = 0x00;
 	PORTD = 0xFF;
 	DDRD = 0x00;

	DisplayInitSTD();
	T0Init();
	ADC_init();
	
	printf("000");
	
	DisplayBlink(1000);

	sei();
	Delay(5000);

//	if(err[0]){
//		printf("E%d", err[0]);
//	}
//
	DisplayBlinkOff();
	wdt_enable(100);

	while (1) {

		wdt_reset();

		Delay(1);

		if (IsControlMode()) {

			// extract temperature sensor value
			//-------------------------------------
			if (++cnt_get_i2c > CNT_1_PERIOD) {
				cnt_get_i2c = 0;
				err[0] = 2;
				temperaturaCurenta = Geti2cSensorData();
				err[0] = 0;
				GoToX(0);
				printf("%d", temperaturaCurenta);
			}

		} else {
			// extract ADC data value
			//-------------------------------------
			if (++cnt_get_adc > CNT_1_PERIOD) {
				cnt_get_adc = 0;

				int adcValBrut = GetADC(ADC_CH_BRUT);
				int adcValFin = GetADC(ADC_CH_FIN);

				// de adaugat filtre ??


				long setValue = adcValBrut + adcValFin / 10;

				long tempValue = (setValue * T_RANGE)/ ADC_MAX;

				temperaturaSetata = tempValue + T_MIN;

				GoToX(0);
				printf("%3d", temperaturaSetata);
			}
		}








	}
	
	
}

