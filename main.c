#include<avr/io.h>
#include<avr/iom128.h>
#include<avr/pgmspace.h>
#include<avr/interrupt.h>
#include<string.h> 
 
#include "define.h"
#include "serial.h" 
#include "Fontlook.h" 
#include"EEPROM.h"
#include "JoinFunction.h"
#include "Telugu_letter_disp.h"
#include "serial_interrupt.h"
#include "Function.h"
#include "disp.h"


int main(void) 
{ 


	DDRA=0xFF;         //port setting for display        
	PORTA=0x00;
	
	DDRC=0xFF;
	PORTC=0x00;

	DDRE=0xFF;			//port setting for memory  
	PORTE=0x00;
 
	DDRD=0xFF;   
	PORTD=(1<<PD2);
	 
	DDRB=0xFF;			//OCR Port setting
	PORTB=(0<<PB2)|(0<<PB3);
	PORTB=(1<<PB7);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
	PORTB=(1<<PB4);

   //glopal initialisation..............  
	Initialise_SerialPort(); 
    t1_timerint();
	t0_pwm_init();		//Initiate timer 0,1 for PWM (multicolour) 
	t2_pwm_init();
 	Init_EEPROM();
   	sei();

 

	OCR_value1=0;		//red
	OCR_value2=255;	


	Lang=0; 
 	Slogan();

	PORTA=0; 
	PORTC=0; 
	RecCtr=0;
	  
 	MyPort_SendStr("Application Restart..");
	while(1)   
	{  
		//	MyPort_SendByte('A'); 
		//	DebugPort_SendByte('F'); 
    		 
	/*	if(TFlag==0)          //Timer Interrupt action Here
		{
    		if(PORTB & 0x01)
			{
			    PORTB = PINB & ~0x01; // on
			} 
		    else                   
			{
				PORTB = PINB | 0x01; // off 
			}
			TFlag=1;
		}*/
		DispScrKing();

	} 
	return 1;
}

