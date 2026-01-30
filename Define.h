#define BYTE unsigned char
#define WORD unsigned int
#define LONG unsigned long int

#define ROWPORT1		PORTA
#define ROWPORT2		PORTC

#define OCLK_1   PORTD|=0x40        	 //6 pin     
#define OCLK_0   PORTD&=0xBF

#define BLANK_1   PORTD|=0x80   		//7 pin           
#define BLANK_0   PORTD&=0x7F

#define SCLK_1   PORTD|=0x20    		// 5 pin         
#define SCLK_0   PORTD&=0xDF

#define SDA_1   PORTD|=0x10    			// 4 pin      	 
#define SDA_0   PORTD&=0xEF

#define TELUGU_ADD 100

BYTE  FontSh[160];
WORD DispArray[1300],ColCtr=0;

WORD TimerCtr=0;
volatile BYTE TFlag=0;

BYTE RecCtr=0;
BYTE i3=0;

BYTE SerialFlag;						//serial interrupt
WORD SerialTimeOutCtr;
WORD  i,j;

BYTE val=0,val1=0,CrcValue=0;			// CRC Checking

LONG Addresstoread=0,Addresstoread1=0;
BYTE Lang;
BYTE Eng_Flag=0,Eng_Flag_Hindi=0;
BYTE TimeOutFlag=0;
WORD TimeOutCtr=0;


BYTE var1=0;							// multicolour
volatile unsigned char OCR_value1,OCR_value2;

BYTE RecVal=0,DispTypeFlag=0,Slogonindex=0,DispCount=0,SloganLetter,PreviousType=0;		/// Disp method
BYTE EngData=0,HindiData=0,TeluguData=0;
WORD FontCount,TrainNoCount=0;
BYTE date_flag=0;

BYTE RecBuffer[190];
BYTE Eng_Sta_Name[30],Hind_Sta_Name[30],Telu_Sta_Name[30];
BYTE Eng_Msg[160],Hind_Msg[160],Telu_Msg[160];
BYTE KmArr[10];
BYTE Date_Time[25];
BYTE Train_No[25];

#define TrNO_Size 25
#define StaName_Size  30
#define DateTime_Size 20
#define Msg_Size 135
#define KM_Size 10

void InitDisp(BYTE TotalFonts);

const  char Eng_Slog[] PROGMEM ="WISH YOU HAPPY JOURNEY~";
const  char Rail_Slog[] PROGMEM="SOUTH CENTRAL RAILWAYS WELCOMES YOU~";

const  char TrNOE[] PROGMEM ="THE TRAIN NO IS: ~";
const  char AtWelE[] PROGMEM =" WELCOMES YOU~";
const  char KME[] PROGMEM =" KM AWAY~";


const  BYTE TrNOH[] PROGMEM ={0x17,0x3E,0x21,0x3C,0x40,0x00,0x28,0x02,0x2C,0x30,0x00,'~'};
const  BYTE AtWelH[] PROGMEM ={0x00,0x06,0x2A,0x00,0x15,0x3E,0x00,0x38,0x4D,0x35,0x3E,0x17,0x24,0x00,0x15,0x30,0x24,0x3E,0x00,0x39,0x48,'~'};
const  BYTE KMH[] PROGMEM ={0x00,0x15,0x3F,0x32,0x4B,0x2E,0x40,0x1F,0x30,0x0,0x26,0x42,0x30,0x0,0x39,0x48,'~'};


const  BYTE TrNOT[] PROGMEM ={1,107,1,129,0,0,1,14,6,225,1,47,1,111,0,0,'~'};
const  BYTE AtWelT[] PROGMEM ={0,0,1,194,1,191,6,184,0,43,0,212,6,225,'~'};
const  BYTE KMT[] PROGMEM ={0,0,0,19,1,76,0,0,0,243,1,99,6,225,1,135,0,0,0,5,1,8,6,176,0,240,'~'};


BYTE  CRC(BYTE len)
{

	BYTE Temp;

	volatile BYTE  ValCRC;

	ValCRC=0;

   	for(Temp=0;Temp<len;)
   	{

       	ValCRC^=RecBuffer[Temp];

		//if(RecBuffer[Temp]=='~')
		//break;

		Temp++;

   	}
 	return ValCRC;
}



void Seri2Disp(void);
void Delay1(void)
{
	BYTE x,y;

  	 for(x=0;x<15;x++)
     for(y=0;y<17;y++);
}



#define SIZE 			16			// Hindi join letter functions
#define	BACK_SIZE 		 7
#define FRONT_SIZE 		 2
#define TOP_SIZE 		12
#define BOTTOM_SIZE 	 8



BYTE Temp1, CheckFlag, HalfLetterFlag =0, FrontjoinFlag =0;
BYTE index1, DecreaseColctr = 0, RaDown = 0;		//index,
WORD ch, ch1,ch2,ch3,ch4,LastLetter ,MainLetter;		//Chr,Chr1,
WORD TopJoinIndex,BackJoinIndex,BottomJoinIndex, Value;
WORD ColCtr1,ColCtr2; //, FrontJoinCounter = 0, FrontJoinArray[];
BYTE  joinindex, IncrementCount, Uniqueletter1;

WORD Back_Join_Letters_Algorithm(WORD,WORD);
WORD Top_Join_Letters_Algorithm(WORD,WORD);
WORD Bottom_Join_Letters_Algorithm(WORD,WORD,WORD);
WORD Front_Join_Algorithm(WORD,WORD,WORD);
WORD DoubleJoin_Algorithm(WORD,WORD,WORD,WORD);
WORD SingleDoubleLetter_Algorithm(WORD,WORD,WORD);

BYTE Valarr[10]={0x30,0x2C,0x2D,0x17,0x18,0x27,0x2E,0x28,0x2F,0x35};
BYTE Valarr1[5] = {0x23, 0x28, 0x2F, 0x32, 0x35};
BYTE Valarr2[4] = {0x35, 0x28, 0x1A, 0x32};



BYTE MainLetters[SIZE] PROGMEM=
{
25,27,31,32,33,34,38,48,49,51,52,57,61,92,93,97,
/*
4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,
43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,61,80,88,89,90,91,92,93,94,95,96,97,100,101,102,103,104,105,
106,107,108,109,110,111,112,113,114,115,116,117,118,119,121,122,123,124,125,126,127,*/
};

BYTE Back_JoinLetter_Array[BACK_SIZE] PROGMEM=
{

3,
59,
62,
64,
73,
//74,
75,
76,
//79,
};
/*
unsigned int const Front_JoinLetter_Array[FRONT_SIZE] PROGMEM=
{
63,78,
};
*/
BYTE Top_JoinLetter_Array[TOP_SIZE] PROGMEM=
{

1,
2,
58,                //  NOT USE
69,                
70,
71,                //   NOT USE
72,
81,                 //    not use
83,                  //    not use
84,                  //  not use
85,               //   not use

};

BYTE Bottom_JoinLetter_Array[BOTTOM_SIZE] PROGMEM =
{
60,
65,
66,
67,
77,
82,               // not use
86,               //  not use
87,                //  not use
};


void InterruptJoin(WORD);



BYTE NumCount=0;
	volatile BYTE AVAL1,CheckByte,CheckFlag2=0,CheckFlag3=0;  //index3,index2,
    volatile WORD ch0,Chr,Chr1,Chr2,CheckWord;    //ch1,ch2,ch1,BackJoinIndex,FrontJoinIndex,TopJoinIndex,BottomJoinIndex	//
   	WORD  value3,DISPLAYINDEX,firsvalue,Firstvalue, Secondvalue,telindex;//TeluguFontIndex[100];
//BYTE breakCount=0,breakFlag=0;
	

unsigned int Back_JoinLetter_Search(unsigned int  value)
{
int low=0,high=BACK_SIZE-1,mid;

   ///WATCHDOG=~WATCHDOG;
   while(low <= high)
   {
      ///WATCHDOG=~WATCHDOG;
      mid=(low+high)/2;
      if(pgm_read_byte(&Back_JoinLetter_Array[mid]) < value)
         low=mid+1;
      else if(pgm_read_byte(&Back_JoinLetter_Array[mid]) > value)
         high=mid-1;
      else if(pgm_read_byte(&Back_JoinLetter_Array[mid]) == value)
         return mid;
      ///WATCHDOG=~WATCHDOG;
   }       
   ///WATCHDOG=~WATCHDOG;

   if(high == -1)
      return 0;
   if(low == BACK_SIZE)
      return (BACK_SIZE-1);
   if(low-high == 1)
      return high;
   ///WATCHDOG=~WATCHDOG;
   return 0;
}




unsigned int Front_JoinLetter_Search(unsigned int  value)
{
int low=0,high=SIZE-1,mid;

   ///WATCHDOG=~WATCHDOG;
   while(low <= high)
   {
      ///WATCHDOG=~WATCHDOG;
      mid=(low+high)/2;
      if(pgm_read_byte(&MainLetters[mid]) < value)
         low=mid+1;
      else if(pgm_read_byte(&MainLetters[mid]) > value)
         high=mid-1;
      else if(pgm_read_byte(&MainLetters[mid]) == value)
         return mid;
      ///WATCHDOG=~WATCHDOG;
   }       
   ///WATCHDOG=~WATCHDOG;

   if(high == -1)
      return 0;
   if(low == SIZE)
      return (SIZE-1);
   if(low-high == 1)
      return high;
   ///WATCHDOG=~WATCHDOG;
   return 0;
}




unsigned int Top_JoinLetter_Search(unsigned int  value)
{
int low=0,high=TOP_SIZE-1,mid;

   ///WATCHDOG=~WATCHDOG;

   while(low <= high)
   {
      ///WATCHDOG=~WATCHDOG;
      mid=(low+high)/2;
      if(pgm_read_byte(&Top_JoinLetter_Array[mid]) < value)
         low=mid+1;
      else if(pgm_read_byte(&Top_JoinLetter_Array[mid]) > value)
         high=mid-1;
      else if(pgm_read_byte(&Top_JoinLetter_Array[mid]) == value)
         return mid;
      ///WATCHDOG=~WATCHDOG;
   }  
        
   ///WATCHDOG=~WATCHDOG;

   if(high == -1)
      return 0;
   if(low == TOP_SIZE)
      return (TOP_SIZE-1);
   if(low-high == 1)
      return high;
   ///WATCHDOG=~WATCHDOG;
   return 0;
}




unsigned int Bottom_JoinLetter_Search(unsigned int  value)
{
int low=0,high=BOTTOM_SIZE-1,mid;

   
   while(low <= high)
   {
      
      mid=(low+high)/2;
      if(pgm_read_byte(&Bottom_JoinLetter_Array[mid]) < value)
         low=mid+1;
      else if(pgm_read_byte(&Bottom_JoinLetter_Array[mid]) > value)
         high=mid-1;
      else if(pgm_read_byte(&Bottom_JoinLetter_Array[mid]) == value)
         return mid;
      
   }       


   if(high == -1)
      return 0;
   if(low == BOTTOM_SIZE)
      return (BOTTOM_SIZE-1);
   if(low-high == 1)
      return high;
   return 0;

}



