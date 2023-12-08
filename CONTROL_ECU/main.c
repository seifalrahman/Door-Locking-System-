/*
 * main.c
 *
 *  Created on: Oct 30, 2023
 *      Author: seif alrahman
 */
#define OPEN_DOOR '+'
#define CHANGE_PASSWORD '-'
#define PASSWORD_ADDRESS 1000


#include "std_types.h"
#include "common_macros.h"
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "Timer1.h"
#include "twi.h"
#include "uart.h"
#include "buzzer.h"
#include "external_eeprom.h"
#include "dc_motor.h"

Timer1_ConfigType Timer_Config= {65534,0,F_CPU_1024,Normal} ;
volatile uint8 cnt=0;
void addNewPassword(void){
	uint8 flag =0;
	uint8 i=0 ;
	uint8 matchedFlag =0 ;
	uint8 passWord_1[6];
	uint8 passWord_2[6];
	while(!matchedFlag){
		flag=0;
		UART_receiveString(passWord_1);
		UART_receiveString(passWord_2);
		for (i=0;i<5;i++){
			if(passWord_1[i]!=passWord_2[i]){
				flag=1;
				UART_sendByte(0);
				break ;
			}
		}
		if(!flag){
			matchedFlag=1;
			UART_sendByte(1);
			for(i=0;i<5;i++){
				EEPROM_writeByte(PASSWORD_ADDRESS+i,passWord_1[i]);
				_delay_ms(10);
			}
		}
	}
}

void doorProcedures(void){


	if(cnt==0){

		Timer_Config.initial_value=13885;

		Timer1_init(&Timer_Config);
		cnt++;
	}else if (cnt==1){

		Timer_Config.initial_value=0;

		Timer1_init(&Timer_Config);
		cnt++;
	}else if (cnt==2){


		Timer_Config.initial_value=42099 ;
		Timer1_init(&Timer_Config);
		cnt++;
	}else if (cnt==3){

		Timer_Config.initial_value=13885;

		Timer1_init(&Timer_Config);
		cnt++;
	}else if (cnt==4){

		cnt++;
	}else if (cnt==5){

		Timer1_deInit() ;
		Timer_Config.initial_value=65534 ;
		cnt++;
	}
}
void checkCount(void){
	while(1){
		uint8 state;
		if(cnt==0){
			state=CW;
			DcMotor_Rotate(state,100);
		}else if (cnt==1){

		}else if (cnt==3){
			state=OFF ;
			DcMotor_Rotate(state,0);

		}else if (cnt==4){
			state=A_CW ;

			DcMotor_Rotate(state,100);

		}else if (cnt==5){

		}else if (cnt==6){
			state=OFF;
			DcMotor_Rotate(state,0);

			cnt=0;
			break;
		}
	}
}

void main (void){
	uint8 passWord_2[6];
	uint8 mainSystemOption;
	uint8 charread;
	uint8 i=0 ,i2=0 ;
	SREG|=(1<<7);
	uint8 flag =1;
	TWI_ConfigType Config={5,2}  ;
	UART_ConfigType UART_Config ={EightDataBits,EvenParity,OneBit,9600} ;
	TWI_init(&Config);
	UART_init(&UART_Config) ;
	DcMotor_Init();
	Buzzer_init();
	addNewPassword();
	DcMotor_Rotate(OFF,0);
	while(1){
		mainSystemOption=UART_recieveByte();
		if(mainSystemOption==OPEN_DOOR){

			for(i=0;i<3;i++){
				flag=1;
				UART_receiveString(passWord_2);
				for(i2=0;i2<5;i2++){
					EEPROM_readByte(PASSWORD_ADDRESS+i2,&charread);
					_delay_ms(10);
					if(passWord_2[i2]!=charread){
						UART_sendByte(0);
						flag=0;
						break;
					}
				}
				if(flag){
					UART_sendByte(1);
					Timer1_setCallBack(doorProcedures) ;
					Timer1_init(&Timer_Config);
					checkCount();
					break ;}

			} if (!flag){
				Buzzer_on();
				_delay_ms(60000);
				Buzzer_off();
			}

		}else if(mainSystemOption==CHANGE_PASSWORD){
			for(i=0;i<3;i++){
				flag=1;
				UART_receiveString(passWord_2);
				for(i2=0;i2<5;i2++){
					EEPROM_readByte(PASSWORD_ADDRESS+i2,&charread);
					_delay_ms(10);
					if(passWord_2[i2]!=charread){
						UART_sendByte(0);
						flag=0;
						break;
					}
				}
				if(flag){

					UART_sendByte(1);
					addNewPassword();
					break ;}

			}
			if(!flag){
				Buzzer_on();
				_delay_ms(60000);
				Buzzer_off();
			}
		}

	}



}
