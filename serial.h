#define USART_BAUD 115200ul
#define USART_UBBR_VALUE ((F_CPU/(USART_BAUD<<4))-1)

#define CPU_CLK 8000000
#define PERIOD_MS 400


void Initialise_SerialPort(void)
{

//	Tx0 is used as Debug Port
//	Rx0 is used to detect GPS Datas

	UCSR0C=(0<<UMSEL0)|(1<<UCSZ01)|(1<<UCSZ00);													
	UBRR0H=0;	// 4800 Baud
	UBRR0L=143;	//143- 4800 Baud
				//71-9600 Baud
				//207 -4800
				//103-9600
	UCSR0B=( (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0) );
	

	UCSR1C=(0<<UMSEL1)|(1<<UCSZ11)|(1<<UCSZ10);

	UBRR1H=0;	// 4800 Baud
	UBRR1L=143;	// 4800 Baud
	UCSR1B=( (1<<TXEN1) | (1<<RXEN1) | (1<<RXCIE1) );

}
	
void t1_timerint(void)  	//this is for timer initialization
{

	// Start timer 1 with clock prescaler CLK/1024 and CTC Mode ("Clear Timer on Compare")
	// Resolution is 139 us 
	// Maximum time is 9.1s 

	TCCR1A = (0<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<COM1C1)|(0<<COM1C0)|(0<<WGM11) |(0<<WGM10);

	TCCR1B = (0<<ICNC1) |(0<<ICES1) |(0<<WGM13) |(1<<WGM12)|(1<<CS12) |(0<<CS11) |(1<<CS10);

	TCNT1 = 0;		// Reset time

	OCR1A = (WORD)(((CPU_CLK/1024)*PERIOD_MS)/1000) - 1;	//Calculate and set delay

	TIMSK |= (1<<OCIE1A);	// Enable interrupt on compare match

}



void t0_pwm_init()		// initialization for Phase Correct PWM signal using timer 0
{
	// WGM0[1:0]= 01, for Phase Correct PWM mode
	// COM0[1:0]= 10, to select non inveting mode
	// CS0[2:0] =010. for prescaler=8
		 
	TCCR0=(1<<WGM00)|(1<<WGM01)|(3<<COM00)|(1<<CS00);
	DDRB|=(1<<PB0);		// selcet OC0 as output pin
	TIMSK|=(1<<OCIE0);	//enable Output compare interrupt
}
 
void t2_pwm_init()	// initialization for Phase Correct PWM signal using timer 2
{		
	// WGM2[1:0]= 11, for Fast PWM mode
	// COM2[1:0]= 10, to select non inveting mode
	// CS2[2:0] =010. for prescaler=8
 
	TCCR2=(1<<WGM20)|(1<<WGM21)|(3<<COM20)|(1<<CS00);
	DDRB|=(1<<PB1);		// selcet OC2 as output pin
	TIMSK|=(1<<OCIE2);	//enable Output compare interrupt
}


void MyPort_SendByte(BYTE Data)
{
    UDR0 = Data;                       // Start transmittion
    while ( !(UCSR0A & (1<<UDRE0)) ); // Wait for empty transmit buffer
    UCSR0A=(1<<UDRE0);
}

void DebugPort_SendByte(BYTE Data)
{
    UDR1 = Data;                       // Start transmittion
   
	while ( !(UCSR1A & (1<<UDRE1)) ); // Wait for empty transmit buffer
    UCSR1A=(1<<UDRE1);
}


void DebugPort_SendStr(char *str1)
{
	BYTE t2=0;
	while(str1[t2])
	{
	    UDR1 = str1[t2];                       // Start transmittion
	   	while ( !(UCSR1A & (1<<UDRE1)) ); // Wait for empty transmit buffer
   		UCSR1A=(1<<UDRE1);
		t2++;
	}
}
void MyPort_SendStr(char *str1)
{
	BYTE t2=0;
	while(str1[t2])
	{
	    UDR0 = str1[t2];                       // Start transmittion
	   	while ( !(UCSR0A & (1<<UDRE0)) ); // Wait for empty transmit buffer
   		UCSR0A=(1<<UDRE0);
		t2++;
	}
}

ISR(SIG_OUTPUT_COMPARE1A)   //this for timer interrupt
{


	TimeOutCtr++;
	if(TimeOutCtr>1000)
	{
		TimeOutCtr=0;
		TimeOutFlag=1;

	}

	if(TFlag==1)
	{
		TimerCtr++;
		if(TimerCtr>10)
		{
			TFlag=0;
			TimerCtr=0;
		}
		
	}

	if(SerialFlag == 1)
	{
		SerialTimeOutCtr++;
		if(SerialTimeOutCtr > 6)
		{
			//SerialFlag=0;
		    SerialTimeOutCtr=11;
		//	DebugPort_SendByte('S');
		}

	
	}

}

ISR(TIMER0_COMP_vect)			// interrupt subroutine
{
	OCR0=OCR_value1;			// put OCR value
}
 
ISR(TIMER2_COMP_vect)			// interrupt subroutine
{
	OCR2=OCR_value2;			// put OCR value
}
 


ISR(USART1_RX_vect)								//  For using 1st Channel
{
	BYTE ch1;
//	BYTE ser1_temp=0;

	TimeOutCtr=0;
	TimeOutFlag=0;

	ch1=UDR1;
	UDR0 = ch1;
	
	SerialFlag=1;								// Serial flag will be set as 1.							
	
	RecBuffer[RecCtr]=ch1;
	if(RecCtr<190)
		RecCtr++;

}





