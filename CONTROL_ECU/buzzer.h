/*
 * buzzer.h
 *
 *  Created on: Oct 30, 2023
 *      Author: seif alrahman
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "gpio.h"
/*******************************************
 * 			  CHOOSING PORT and PIN
 *******************************************/
#define BUZZER_PORT  PORTD_ID
#define BUZZER_PIN   PIN7_ID


/*******************************************
 * 			  FUNCTION PROTOTYPES
 *******************************************/

void Buzzer_init();
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* BUZZER_H_ */
