

void Serial_data(void)
{
	WORD temp1=0,CrcValue=0;
	
 //	BYTE xx;

	if((SerialFlag == 1) && (SerialTimeOutCtr > 10) && (RecCtr>10))
	{

		CrcValue=CRC(RecCtr-1);												//CRC Calculation
		MyPort_SendByte(0x0d);
		MyPort_SendByte(0x0a);

	//	MyPort_SendByte(CrcValue);
	//	MyPort_SendByte(RecBuffer[RecCtr-1]);
MyPort_SendByte('A');
		if(CrcValue==RecBuffer[RecCtr-1]  )								//CRC Check
		{

		//	for(xx=0;xx<RecCtr;xx++)
		//		MyPort_SendByte(RecBuffer[xx]);
			 if(PreviousType!=RecBuffer[3])									// Display data reset
			 {
			 	EngData=0,HindiData=0,TeluguData=0;
				DispCount=1;
				PreviousType=RecBuffer[3];
				MyPort_SendByte('S');
			 }
			 else
			 	PreviousType=RecBuffer[3];

		    temp1=4;
			RecVal=0;
			if(RecBuffer[2] =='1'  && RecBuffer[3] =='5') 				// Train Number Rec
			{
				TrainNoCount=0;
				DispTypeFlag=1;
				

				while(RecBuffer[temp1] != '~')
				{
					Train_No[RecVal] = RecBuffer[temp1++];
					//MyPort_SendByte(Train_No[RecVal]);
					RecVal++;
					if (RecVal>TrNO_Size)										
						break;				
				}Train_No[RecVal++] ='~';
			}
			else if(( RecBuffer[3] =='1' || RecBuffer[3] =='2' || RecBuffer[3] =='4'))			//Source Station
			{
				RecVal=0;
				if(RecBuffer[3] =='2')
					DispTypeFlag=4;
				else
					DispTypeFlag=2;
				if(RecBuffer[0] =='0')									//English
				{
				  EngData=1;
				  while(RecBuffer[temp1] != '~')										// English Station name
				  {
						Eng_Sta_Name[RecVal++] = RecBuffer[temp1++];
						if (RecVal>StaName_Size )
							break;
					
				  }	Eng_Sta_Name[RecVal++] ='~';
				  
				}
				else if(RecBuffer[0] =='1')												// Hindi Station Name
				{
				  HindiData=1;
				  while(RecBuffer[temp1] != '~')
				  {
						Hind_Sta_Name[RecVal++] = RecBuffer[temp1++];
						if (RecVal>StaName_Size)
							break;
					
				  }	Hind_Sta_Name[RecVal++] ='~';
				}
				else if(RecBuffer[0] =='2')												// Telugu Station name
				{
				  TeluguData=1;
				  while(RecBuffer[temp1] != '~')
				  {
						Telu_Sta_Name[RecVal++] = RecBuffer[temp1++];
						if (RecVal>StaName_Size)
							break;
					
				  }	Telu_Sta_Name[RecVal++] ='~';
				}
				  temp1++;
				  RecVal=0;
				  while(RecBuffer[temp1] != '~')										// Train number
				  {
						Train_No[RecVal++] = RecBuffer[temp1++];
						if (RecVal>TrNO_Size)
						{
							Train_No[RecVal++] ='~';
							break;
						}
				  }Train_No[RecVal++] ='~';
				  temp1++;
				  RecVal=0;
				  while(RecBuffer[temp1] != '~')										// Date & Time
				  {
						Date_Time[RecVal++] = RecBuffer[temp1++];
						if (RecVal>DateTime_Size)
							break;
					
				  }Date_Time[RecVal++] ='~';
				  //temp1++;
				 // RecVal=0;
				
			}
			else if(( RecBuffer[3] =='3'))											//Next Station
			{
				RecVal=0;
				DispTypeFlag=3;
				temp1=4;
				if(RecBuffer[0] =='0')												//English Station name
				{
				  EngData=1;
				  while(RecBuffer[temp1] != '~')
				  {
				  	
						Eng_Sta_Name[RecVal++] = RecBuffer[temp1++];
						//	MyPort_SendByte(Eng_Sta_Name[RecVal++]);
						if (RecVal>StaName_Size)
							break;
					
				  }	Eng_Sta_Name[RecVal++] ='~';

				  temp1++;
				  RecVal=0;
				  while(RecBuffer[temp1] != '~')									// English KM Away
				  {
				  
						KmArr[RecVal++] = RecBuffer[temp1++];
						//	MyPort_SendByte(KmArr[RecVal++]);
						if (RecVal>KM_Size)
							break;
					
				  }	KmArr[RecVal++] ='~';

				  temp1++;
				  RecVal=0;
				  while(RecBuffer[temp1] != '~')									//English Message
				  {
				  //	MyPort_SendByte(RecBuffer[temp1]);
						Eng_Msg[RecVal++] = RecBuffer[temp1++];
						if (RecVal>Msg_Size)
						{
							Eng_Msg[RecVal++] ='~';
							break;
						}
				  }	Eng_Msg[RecVal++] ='~';
				}
				else if(RecBuffer[0] =='1')									// Hindi
				{
				  HindiData=1;
				  while(RecBuffer[temp1] != '~')									//Hindi Station name
				  {
						Hind_Sta_Name[RecVal++] = RecBuffer[temp1++];
						if (RecVal>StaName_Size)
							break;
					
				  }	Hind_Sta_Name[RecVal++] ='~';
				  temp1++;
				  RecVal=0;
				  while(RecBuffer[temp1] != '~')									// English KM Away
				  {
						KmArr[RecVal++] = RecBuffer[temp1++];
						if (RecVal>KM_Size)
							break;
					
				  }	KmArr[RecVal++] ='~';

				  temp1++;
				  RecVal=0;
				  while(RecBuffer[temp1] != '~')									// Hindi Message
				  {
						Hind_Msg[RecVal++] = RecBuffer[temp1++];
						if (RecVal>Msg_Size)
						{
							Hind_Msg[RecVal++] ='~';
							break;
						}
				  }Hind_Msg[RecVal++] ='~';
				}
				else if(RecBuffer[0] =='2')									// Telugu
				{
				  TeluguData=1;
				  while(RecBuffer[temp1] != '~')									// Station name in telugu
				  {
						Telu_Sta_Name[RecVal++] = RecBuffer[temp1++];
						if (RecVal>StaName_Size)
							break;
					
				  }	Telu_Sta_Name[RecVal++] ='~';
				  temp1++;
				  RecVal=0;
				   while(RecBuffer[temp1] != '~')									// English KM Away
				  {
						KmArr[RecVal++] = RecBuffer[temp1++];
						if (RecVal>KM_Size)
							break;
					
				  }	KmArr[RecVal++] ='~';

				  temp1++;
				  RecVal=0;
				  while(RecBuffer[temp1] != 0xFF)									// Telugu Message
				  {
						Telu_Msg[RecVal++] = RecBuffer[temp1++];
						if (RecVal>Msg_Size)
						{
							//Telu_Msg[RecVal++] ='~';
							break;
						}
				  }Telu_Msg[RecVal++] =0xFF;
				}
				 
				  temp1++;
				  RecVal=0;
				  while(RecBuffer[temp1] != '~')										// Date @ time value
				  {
						Date_Time[RecVal++] = RecBuffer[temp1++];
						if (RecVal>DateTime_Size)
							break;
					
				  }Date_Time[RecVal++] ='~';
				  //temp1++;
				 // RecVal=0;
				
			}

MyPort_SendByte('M');
		}//crc

		SerialFlag=0;
		RecCtr=0;
		SerialTimeOutCtr=0;
		CrcValue=0;

	
	}
}


