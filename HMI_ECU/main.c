/*
 * main.c
 *
 *  Created on: Oct 30, 2023
 *      Author: seif alrahman
 */
#define OPEN_DOOR '+'
#define CHANGE_PASSWORD '-'
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "std_types.h"
#include "common_macros.h"
#include "uart.h"
#include "Timer1.h"
#include "lcd.h"
#include "keypad.h"

Timer1_ConfigType Config= {65534,0,F_CPU_1024,Normal} ;

uint8 notMatchedProcedure(void){
	uint8 matchedFlag =0 ;
	uint8 i=0,i2;
	uint8 passWord_temp[6] ;
	passWord_temp[5]='#' ;
	for(i=0;i<2;i++){
		LCD_clearScreen() ;
		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1,0);
		for(i2=0; i2<5 ; i2++){
			passWord_temp[i2]=KEYPAD_getPressedKey() ;
			LCD_displayCharacter('*');
			_delay_ms(750);


		}
		while(KEYPAD_getPressedKey()!=ENTER);
		_delay_ms(750);
		UART_sendString(passWord_temp);
		matchedFlag=UART_recieveByte();
		if(matchedFlag){
			return matchedFlag ;
		}
	}
	return matchedFlag ;
}
volatile uint8  cnt=0 ;
void doorProcedures(void){



	if(cnt==0){
		Config.initial_value=13885 ;
		Timer1_init(&Config);
		cnt++;
	}else if (cnt==1){

		cnt++;
	}else if (cnt==2){

		Config.initial_value=42099 ;
		Timer1_init(&Config);
		cnt++;
	}else if (cnt==3){
		Config.initial_value=13885;
		cnt++;
		Timer1_init(&Config);
	}else if (cnt==4){
		cnt++;
	}else if (cnt==5){

		Config.initial_value=65534 ;

		Timer1_deInit() ;
		cnt++;
	}

}
void checkCount (void){
	while(1){
		if(cnt==0){
			LCD_moveCursor(0,0);
			LCD_displayString("Unlock the Door");

		}else if (cnt==3){
			LCD_clearScreen();

		}else if (cnt==4){
			LCD_moveCursor(0,0);
			LCD_displayString("DOOR is Locking  ") ;

		}else if (cnt==6){
			cnt=0;
			break ;
		}
	}
}
void addNewPassword(void){
	sint8 passWord_1[6] ;
	sint8 passWord_2[6] ;
	uint8 counter =0 ;
	uint8 matchedFlag =0 ;
	passWord_1[5]='#';
	passWord_2[5]='#';


	while(!matchedFlag){
		LCD_clearScreen() ;
		LCD_displayString("plz enter pass:");
		LCD_moveCursor(1,0);
		for(counter=0; counter<5 ; counter++){
			passWord_1[counter]=KEYPAD_getPressedKey() ;

			LCD_displayCharacter('*');
			_delay_ms(750);


		}
		while(KEYPAD_getPressedKey()!=ENTER);
		_delay_ms(750);
		LCD_clearScreen() ;
		LCD_displayString("plz re-enter the");
		LCD_moveCursor(1,0) ;
		LCD_displayString("same pass:");
		for(counter=0; counter<5 ; counter++){
			passWord_2[counter]=KEYPAD_getPressedKey() ;
			LCD_displayCharacter('*');
			_delay_ms(750);

		}
		while(KEYPAD_getPressedKey()!=ENTER);
		_delay_ms(750);
		UART_sendString(passWord_1);
		UART_sendString(passWord_2);
		matchedFlag=UART_recieveByte();


	}
}

void main (void){
	UART_ConfigType UART_Config ={EightDataBits,EvenParity,OneBit,9600} ;
	uint8 matchedFlag =0 ;
	uint8 changed=0;
	uint8 passWord_2[6] ;
	uint8 counter =0 ;
	uint8 mainSystemOption;
	SREG|=(1<<7);
	passWord_2[5]='#';

	LCD_init();



	UART_init(&UART_Config);
	addNewPassword();

	while (1){

		LCD_clearScreen();
		changed=0;
		LCD_moveCursor(0,0);
		LCD_displayString("+ : Open Door");
		LCD_moveCursor(1,0);
		LCD_displayString("- : Change Pass");

		mainSystemOption=KEYPAD_getPressedKey() ;
		_delay_ms(750);
		LCD_clearScreen() ;
		if(mainSystemOption==OPEN_DOOR){
			UART_sendByte(OPEN_DOOR);
			LCD_displayString("plz enter pass:");
			LCD_moveCursor(1,0);
			for(counter=0; counter<5 ; counter++){
				passWord_2[counter]=KEYPAD_getPressedKey() ;
				LCD_displayCharacter('*');
				_delay_ms(750);

			}
			while(KEYPAD_getPressedKey()!=ENTER);
			_delay_ms(750);
			UART_sendString(passWord_2);
			matchedFlag=UART_recieveByte() ;
			if(!matchedFlag){
				matchedFlag=notMatchedProcedure();
			}else{
				LCD_clearScreen();
				LCD_displayString("TRUE");
				_delay_ms(600);
				LCD_clearScreen();

				Timer1_setCallBack(doorProcedures) ;
				Timer1_init(&Config);

				changed=1 ;
				checkCount();
			}
			if(!matchedFlag){
				LCD_clearScreen();
				LCD_displayString("INCORRECT ENTRY") ;


				_delay_ms(60000) ;
				LCD_clearScreen();
			}else if (!changed){
				LCD_clearScreen();
				LCD_displayString("TRUE");
				_delay_ms(600);
				LCD_clearScreen();
				Timer1_setCallBack(doorProcedures) ;
				Timer1_init(&Config);
				checkCount();
			}


		}else if (mainSystemOption==CHANGE_PASSWORD){
			UART_sendByte(CHANGE_PASSWORD);
			LCD_displayString("plz enter pass:");
			LCD_moveCursor(1,0);
			for(counter=0; counter<5 ; counter++){
				passWord_2[counter]=KEYPAD_getPressedKey() ;
				LCD_displayCharacter('*');
				_delay_ms(750);

			}
			while(KEYPAD_getPressedKey()!=ENTER);
			_delay_ms(750);
			UART_sendString(passWord_2);
			matchedFlag=UART_recieveByte() ;
			if(!matchedFlag){
				matchedFlag=notMatchedProcedure();
			}else{
				LCD_clearScreen();
				LCD_displayString("TRUE");
				_delay_ms(600);
				LCD_clearScreen();
				addNewPassword() ;
				changed=1;

			}
			if(!matchedFlag){
				LCD_clearScreen();
				LCD_displayString("INCORRECT ENTRY") ;
				_delay_ms(60000) ;
				LCD_clearScreen();

			}else if(!changed){
				changed=1 ;
				LCD_clearScreen();
				LCD_displayString("TRUE");
				_delay_ms(600);
				LCD_clearScreen();
				addNewPassword() ;
			}

		}

	}
}
