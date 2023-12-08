/*
 * dc_motor.h
 *
 *  Created on: Oct 13, 2023
 *      Author: seif alrahman
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

typedef enum {
	OFFMotor,CW,A_CW
} DcMotor_State ;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed) ;

#endif /* DC_MOTOR_H_ */
