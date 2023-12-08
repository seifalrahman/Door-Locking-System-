/*
 * dc_motor.c
 *
 *  Created on: Oct 13, 2023
 *      Author: seif alrahman
 */

#include "gpio.h"
#include "Timer0.h"
#include "dc_motor.h"

void DcMotor_Init(void){
	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);

}

void DcMotor_Rotate(DcMotor_State state,uint8 speed) {
	switch(state){
	case OFFMotor:GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
			 GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
			 break;
	case CW:GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_HIGH);
	 	    GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
	 	    break;
	case A_CW:GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
	 	 	  GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_HIGH);
	 	 	  break;
	}

	Timer0_PWM_Init(speed);


}

