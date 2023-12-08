/*
 * Timer1.h
 *
 *  Created on: Oct 13, 2023
 *      Author: seif alrahman
 */

#ifndef TIMER1_H_
#define TIMER1_H_
#include "std_types.h"
#include "common_macros.h"
static volatile void(*ISR_ptr)(void) ;

/*************************************************************
 * 				TIMER1               Configurations
 *************************************************************/
#define OFF 0
typedef enum{
	NO_CLK=0,F_CPU_1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXTERNAL_CS_FALLING_EDGE,EXTERNAL_CS_RISING_EDGE
}  Timer1_Prescaler;

typedef enum{
	Normal=0,CTC=0b0100
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value; /* it will be used in compare mode only.*/
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

/*************************************************************
 * 				FUNCTION PROTOTYPES
 *************************************************************/
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void) ;
void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
