/*
 * buzzer.c
 *
 *  Created on: Oct 30, 2023
 *      Author: seif alrahman
 */

#include "buzzer.h"
void Buzzer_init(void){
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT) ;
	Buzzer_off() ;

}


void Buzzer_on(void){
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH) ;
}

void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW) ;
}
