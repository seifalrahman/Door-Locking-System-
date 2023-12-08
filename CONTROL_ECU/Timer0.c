#include "Timer0.h"


#include "gpio.h"
#include "avr/io.h"



void Timer0_PWM_Init ( uint8 duty_cycle_percentage ){
	TCNT0=0;
	CLEAR_BIT(TCCR0,FOC0);
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,COM01);
	CLEAR_BIT(TCCR0,COM00);
	OCR0=(((uint32)duty_cycle_percentage)*(255))/100 ;
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
	SET_BIT(TCCR0,CS01);
	CLEAR_BIT(TCCR0,CS02);
	CLEAR_BIT(TCCR0,CS00);



}

