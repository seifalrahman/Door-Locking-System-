#include "Timer1.h"

#include "gpio.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void Timer1_init(const Timer1_ConfigType * Config_Ptr){
TCNT1=Config_Ptr->initial_value ;

OCR1A=Config_Ptr->compare_value ;

TCCR1A=(((Config_Ptr->mode)&3))|(1<<FOC1A) ;

TCCR1B=(Config_Ptr->prescaler)|(((Config_Ptr->mode)>>2)<<3);

if((Config_Ptr->mode)==Normal){

	TIMSK=(1<<TOIE1);

}else if ((Config_Ptr->mode)==CTC){

	TIMSK=(1<<OCIE1A);

}

}
void Timer1_deInit(void) {
	TIMSK =OFF  ;
	TCNT1 =OFF  ;
	TCCR1B=OFF ;
	TCCR1A=OFF ;
	ISR_ptr=NULL_PTR ;
}


void Timer1_setCallBack(void(*a_ptr)(void)){
	ISR_ptr=a_ptr ;
}

ISR(TIMER1_COMPA_vect){
	if(ISR_ptr!=NULL_PTR){
		(*ISR_ptr)();
	}
}
ISR(TIMER1_OVF_vect){
	if(ISR_ptr!=NULL_PTR){
		(*ISR_ptr)();
	}
}


