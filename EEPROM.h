/*-----------------------------------------------------------------------------------------------
Project title:	HPCL	-  Driver board
Company Name:	IQNET SYSTEMS
Author		:	A.SAVARIMUTHU AMBROSE, A.RAMAKRISHNAN
Date        :	FEB 2011							
-------------------------------------------------------------------------------------------------*/


#define EEWrite    0xA0
#define EERead     0xA1

#define EEWrite1    0xA2
#define EERead1     0xA3

#define SCL        0x04           // pe2
#define nSCL       0xFB

#define SDA        0x08             // pe3
#define nSDA       0xF7

#define EEPROM_IN           PINE
#define EEPROM_OUT          PORTE
#define EEPROM_DIR          DDRE

#define EEPROM_DIR_VALUE     0x1C
#define EEPROM_INIT_VALUE    0xEF

void Init_EEPROM(void)                                            //PD5- WP, PB1-CLK, PB0-DATA
{
  EEPROM_DIR= EEPROM_DIR | EEPROM_DIR_VALUE;                       // For SDA,SCLOCK and Write Protect as Output
  EEPROM_OUT=EEPROM_OUT & EEPROM_INIT_VALUE;                       // Make Port PD5 as Zero (Disable Write Protect)
}

void ee_delay(void)
{
 BYTE Temp=0;
  do
  {
    Temp++;
  }while(Temp<20);

}

void SendData_EEPROM(BYTE BData)
{
   BYTE Temp=0x80;
   do
   {
     EEPROM_OUT=EEPROM_OUT&nSCL;
     if (BData & Temp)
       EEPROM_OUT=EEPROM_OUT | SDA;
     else
       EEPROM_OUT=EEPROM_OUT & nSDA;
     ee_delay();
     EEPROM_OUT=EEPROM_OUT | SCL;
     ee_delay();
     Temp>>=1;
  }while(Temp!=0);

}
void Start(void)
{
       EEPROM_OUT=EEPROM_OUT&nSCL;
       EEPROM_OUT=EEPROM_OUT | SDA;
       ee_delay();
       EEPROM_OUT=EEPROM_OUT | SCL;	
       ee_delay();
       EEPROM_OUT=EEPROM_OUT & nSDA;
       ee_delay();
       EEPROM_OUT=EEPROM_OUT&nSCL;
}
void Stop(void)
{
      EEPROM_OUT=EEPROM_OUT&nSCL;
      ee_delay();
      EEPROM_OUT=EEPROM_OUT & nSDA;
      ee_delay();	
      EEPROM_OUT=EEPROM_OUT | SCL;	
      ee_delay();
      EEPROM_OUT=EEPROM_OUT | SDA;
      ee_delay();
}

void Ack(void)
{
	EEPROM_OUT=EEPROM_OUT&nSCL;
        ee_delay();
	EEPROM_OUT=EEPROM_OUT | SCL;
	ee_delay();
	EEPROM_OUT=EEPROM_OUT&nSCL;
}

void Write_EEPROM(unsigned long Address,BYTE WriteData)
{
  
   WORD TempCtr;
   BYTE neweewrite=0;
   BYTE MSB_Address,LSB_Address;
   BYTE temp=(BYTE)(Address>>16);
   temp=temp<<1;
   MSB_Address=(BYTE)(Address >>8);
   LSB_Address=(BYTE)Address;
   neweewrite=EEWrite|temp;
   
   Start();
   
   SendData_EEPROM(neweewrite);
   Ack();
   
   SendData_EEPROM(MSB_Address);
   Ack();
   
   SendData_EEPROM(LSB_Address);
   Ack();
  
   SendData_EEPROM(WriteData);
   Ack();
  
   Stop();
   for (TempCtr=0;TempCtr<10000;TempCtr++);
   ee_delay();

}

BYTE Read_EEPROM(unsigned long Address)
{
   BYTE  TempCtr,Temp=0,neweewrite=0;
   BYTE MSB_Address,LSB_Address;
   BYTE temp=(BYTE)(Address>>16);
   temp=temp<<1;
   MSB_Address=(BYTE)(Address >>8);
   LSB_Address=(BYTE)Address;
   neweewrite=EEWrite|temp;
   Start();
   
   SendData_EEPROM(neweewrite);
   Ack();
   
   SendData_EEPROM(MSB_Address);
   Ack();
  
   SendData_EEPROM(LSB_Address);
   Ack();
  
   Start();
   
   SendData_EEPROM(EERead|temp);
   Ack();
   
   EEPROM_DIR=EEPROM_DIR & nSDA;
   for(TempCtr=8;TempCtr>0;TempCtr--)
   {
      EEPROM_OUT=EEPROM_OUT&nSCL;
      ee_delay();
      EEPROM_OUT=EEPROM_OUT | SCL;
      ee_delay();
      if(EEPROM_IN & SDA)
        Temp=Temp+(0x80>>(8-TempCtr));
        EEPROM_OUT=EEPROM_OUT | SCL;
		
   }
   EEPROM_DIR=EEPROM_DIR|SDA;
   Stop();
  
   return Temp;
}

void Write_EEPROM1(WORD Address,BYTE WriteData)
{
  
   WORD TempCtr;
   BYTE MSB_Address,LSB_Address;
   MSB_Address=(BYTE)(Address >>8);
   LSB_Address=(BYTE)Address;
   Start();
   
   SendData_EEPROM(EEWrite1); 
   Ack();
   
   SendData_EEPROM(MSB_Address);
   Ack();
   
   SendData_EEPROM(LSB_Address);
   Ack();
  
   SendData_EEPROM(WriteData);
   Ack();
  
   Stop();
   for (TempCtr=0;TempCtr<10000;TempCtr++);
   ee_delay();

}

BYTE Read_EEPROM1(WORD Address)
{
   BYTE  TempCtr,Temp=0;
   BYTE MSB_Address,LSB_Address;
   MSB_Address=(BYTE)(Address >>8);
   LSB_Address=(BYTE)Address;
   Start();
   
   SendData_EEPROM(EEWrite1);
   Ack();
   
   SendData_EEPROM(MSB_Address);
   Ack();
  
   SendData_EEPROM(LSB_Address);
   Ack();
  
   Start();
   
   SendData_EEPROM(EERead1);
   Ack();
   
   EEPROM_DIR=EEPROM_DIR & nSDA;
   for(TempCtr=8;TempCtr>0;TempCtr--)
   {
      EEPROM_OUT=EEPROM_OUT&nSCL;
      ee_delay();
      EEPROM_OUT=EEPROM_OUT | SCL;
      ee_delay();
      if(EEPROM_IN & SDA)
        Temp=Temp+(0x80>>(8-TempCtr));
        EEPROM_OUT=EEPROM_OUT | SCL;
		
   }
   EEPROM_DIR=EEPROM_DIR|SDA;
   Stop();
  
   return Temp;
}


