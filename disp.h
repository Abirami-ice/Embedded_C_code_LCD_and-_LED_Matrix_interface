void DipMethod(void);		// function declearation for DispMethod

WORD CodeSt;
WORD CodeEnd;
WORD FrontBlank;
WORD RearBlank;
WORD TotalCodeCtr;
WORD ProcessCtr;

//*****************************************************************************
//This function Writes for the LED on/off(hexadecimal value) information 
//move to DispArray, coresponding letters present in the FontSh array.
//
//Arguments: TotalFonts --> No of elements present in the FontSh array.
//
//Return:    nil
//******************************************************************************
void InitDisp(BYTE TotalFonts) 
{
	WORD Chr;
	BYTE Temp3,indexChang=0;
	ColCtr=0;

	if(Lang==0)						// English 
	{
		if(date_flag==1)			//The Date is display in Amber colour
		{
			OCR_value1=255;			//amber
			OCR_value2=225;
			date_flag=0;
		}
		else						// English slogan display in Red colour
		{
			OCR_value1=0;			//red
			OCR_value2=255;	
		}
	
		Temp3=0;
		for(Temp3=0;Temp3<TotalFonts;Temp3++)
		{
		//	MyPort_SendByte(FontSh[Temp3]);
			ch=FontSh[Temp3];
			indexChang=0;
			
			while(pgm_read_word(&Eng_Font[ch-32][indexChang])!=0x8888)
			{
				Chr=pgm_read_word(&Eng_Font[ch-32][indexChang++]);
				DispArray[ColCtr]=Chr;
				ColCtr++;	
			}
			DispArray[ColCtr++] = 0;
			DispArray[ColCtr++] = 0;
		}
	}
	else if(Lang==1)	// Hindi
	{
	
		
		OCR_value1=255;		// Hindi slogan display in green colour
		OCR_value2=0;
		MyPort_SendByte('H');
		MyPort_SendByte('I');
		Eng_Flag_Hindi=0;
		InterruptJoin(TotalFonts);	
	}
	 
	else if(Lang==2)
	{
		OCR_value1=255; 	// Telugu slogan display in yellow colour
		OCR_value2=50;
		MyPort_SendByte('T');
		MyPort_SendByte('E');
		Eng_Flag=0;
		Telugu_disp(TotalFonts);
	}
	

	CodeSt=0;
	CodeEnd=1;
	FrontBlank=128;
	RearBlank=0;
	ProcessCtr=0;
	TotalCodeCtr=ColCtr+128;
	
}


//*****************************************************************************
//This function Writes for arrange  the serial received data in 
//a order to display in Board 
//
//Arguments: nil
//
//Return:    nil
//******************************************************************************
void DisplayMethod(void)								
{

		switch(DispTypeFlag)		                 	// Switch case based on the type of the displaying station// DispTypeFlag represents the stations it is mentioned in serialinterrupt.h
        {	       

		    case 1:										// SwCase1 baseed on Train number Display		
	   				TrainNoDisp();
					TrainNoCount++;
					break;						
						  
										
			case 2: 									//SwCase 2 Based on Source and destination Station
	   				switch(DispCount)
					{
						case 1: 
								if (EngData==1)									// Move English station name to FontSh array
								{
									Lang=0;
									MyPort_SendStr(" EngSta At ");
									EngStationName();
									DispCount=2;
							    	break;

								}						
							
						case 2:	
								if (HindiData==1)								// Move Hindi station name to FontSh array
								{
									Lang=1;
									MyPort_SendStr(" HindSta ");
									HindStationName();
									DispCount=3;
							    	break;

								}															
					   			
						
					   case 3:		
								if (TeluguData==1)								// Move Telugu station name to FontSh array
								{
									Lang=2;
									MyPort_SendStr(" TeluSta ");
									TeluStationName();
									DispCount=4;
							    	break;

								}							
							
						case 4:	
								if(EngData==1)									// Move train number to FontSh array in English
								{
									Lang=0;
									MyPort_SendStr(" EngTrno ");
					   				EngTrainNumberDisp();					   			
									DispCount=5;
							    	break;
								}															
					   			
						case 5:		
								if(HindiData==1)								// Move train number to FontSh array in Hindi
								{
									Lang=1;
									MyPort_SendStr(" HindTrno ");
					   				HindTrainNumberDisp();					   			
									DispCount=6;
							    	break;
								}					
							
						case 6:																
					   			if(TeluguData==1)								// Move train number to FontSh array in Telugu
								{
									Lang=2;
									MyPort_SendStr(" TeluTrno ");
					   				TeluTrainNumberDisp();					   			
									DispCount=7;
							    	break;
								}
						case 7:													// Move Date/Time to FontSh array											
					   			Lang=0;
				   				DateTimeDisp();					   			
								DispCount=1;
								
						    	break;
							
					}
					break;	
								   		
			case 3: 									//SwCase 3 Based on next Station
	   				switch(DispCount)
					{
						MyPort_SendByte(DispCount/10+0x30);
						MyPort_SendByte(DispCount%10+0x30);
						case 1: 
								if (EngData==1)								// Move English station name to FontSh array
								{
									Lang=0;
									MyPort_SendStr(" EngSta ");
									NextEngStationName();
									DispCount=2;
							    	break;

								}														
							
						case 2:		
								if (HindiData==1)							// Move Hindi station name to FontSh array
								{
									Lang=1;
									MyPort_SendStr(" Hind Sta ");
									NextHindStationName();
									DispCount=3;
							    	break;

								}
																				
					   		
						
					    case 3:		
								if (TeluguData==1)							// Move Telugu station name to FontSh array
								{
									Lang=2;
									MyPort_SendStr(" Tel Sta ");
									NextTeluStationName();
									DispCount=4;
							    	break;

								}							
							
						case 4:	
								if(EngData==1)								// Move English Message to FontSh array 
								{
									Lang=0;
									MyPort_SendStr(" Eng Msg ");
					   				EngMsgDisp();					   			
									DispCount=5;
							    	break;
								}															
					   				
						case 5:		
								if(HindiData==1)							// Move Hindi Message  to FontSh array
								{
									Lang=1;
									MyPort_SendStr(" Hind Msg ");
					   				HindMsgDisp();					   			
									DispCount=6;
							    	break;
								}					
							
						case 6:																
					   			if(TeluguData==1)							// Move Telugu Message  to FontSh array
								{
									Lang=2;
									MyPort_SendStr(" Telu MSG ");
					   				TeluMsgDisp();					   			
									DispCount=7;
							    	break;
								}
						case 7:												// Move Date/Time to FontSh array					
					   			Lang=0;
								MyPort_SendStr(" Time ");
				   				DateTimeDisp();					   			
								DispCount=1;
						    	break;
							
					}	
					break;					

			  case 4: 								//SwCase 4 Based on stopping Station
	   				switch(DispCount)
					{
						case 1: 
								if (EngData==1)									// Move English station name to FontSh array
								{
									Lang=0;
								MyPort_SendStr(" EngSta At ");
									EngStationName();
									DispCount=3;
							    	break;

								}						
							
						case 2:																
					   			if(EngData==1)									// Move train number in English
								{
									Lang=0;
									MyPort_SendStr(" EngTrno ");
					   				EngTrainNumberDisp();					   			
									DispCount=3;
							    	break;
								}
						
					   case 3:		
								if (HindiData==1)								// Move Hindi station name to FontSh array
								{
									Lang=1;
									MyPort_SendStr(" HindSta ");
									HindStationName();
									DispCount=5;
							    	break;

								}						
							
						case 4:																
					   			if(HindiData==1)								// Move train number in Hindi
								{
									Lang=1;
									MyPort_SendStr(" HindTrno ");
					   				HindTrainNumberDisp();					   			
									DispCount=5;
							    	break;
								}	
						case 5:		
								if (TeluguData==1)								// Move Telugu station name to FontSh array
								{
									Lang=2;
									MyPort_SendStr(" TeluSta ");
									TeluStationName();
									DispCount=7;
							    	break;

								}						
							
						case 6:																
					   			if(TeluguData==1)								// Move train number in Telugu
								{
									Lang=2;
									MyPort_SendStr(" TeluTrno ");
					   				TeluTrainNumberDisp();					   			
									DispCount=7;
							    	break;
								}
						case 7:													// Move Date/Time to FontSh array				
					   			Lang=0;
				   				DateTimeDisp();					   			
								DispCount=1;
						    	break;
							
					}
					break;	
						
			  				

				default: 										// default slogan
						Lang=0; 
						Slogan();
						break;					
						
						        
        } //switch case end


		
}


//*****************************************************************************
//This function Writes for on/off the LED presend in the the board 
//corresponding to the information in the DispArray.
//
//Arguments: nil
//
//Return:    nil
//******************************************************************************
void DispScrKing(void)																
{

	WORD RowMask;  		
	WORD iRow,iCol;
	BYTE speed;

	for(speed=0;speed<1;speed++)	
	{
    	RowMask=0x8000;						
		   
        for(iRow=0;iRow<16;iRow++)       	
        {
        	
			OCLK_0;							
		
		//	Delay1();
		//	Delay1();
		//	Delay1();
		//	Delay1();
		


            for(iCol=0;iCol<RearBlank;iCol++)
            {
				   	  
            	SCLK_0;
                SDA_0;
                SCLK_1;
			}
            for(iCol=CodeEnd;iCol>CodeSt;iCol--)
            {
                     		
            	SCLK_0;
                if( (DispArray[iCol-1] & RowMask) == RowMask)
                {
                	SDA_1;
                }
                else
                {
                	SDA_0;
                }
                SCLK_1;
        	}
            for(iCol=0;iCol<FrontBlank;iCol++)
            {
				   		
            	SCLK_0;
            	SDA_0;
                SCLK_1;
            }
                     	 
			OCLK_1;
	 		
			PORTA=(BYTE)RowMask;
			PORTC=(BYTE)(RowMask>>8);
		   
		   	RowMask=RowMask>>1;	
			
			
				   									
      	}

	}
	ProcessCtr++;
	if(FrontBlank > 0)
		FrontBlank--;
   	else
    	CodeSt++;
   	if(CodeEnd < ColCtr)
    	CodeEnd++;
   	else
    	RearBlank++;
   	if(ProcessCtr >= TotalCodeCtr)		// this condition will statisfy, when a scrolling is finished.
   	{
		CodeSt=0;
		CodeEnd=1;
		FrontBlank=128;
		RearBlank=0;
		ProcessCtr=0;
		TotalCodeCtr=ColCtr+128;
		if(TimeOutFlag==1)				// this flag is set, when the deriver board doesn't receive any data for a long(5 min) time.
		{
			TimeOutFlag=0;
			Railway_Display();
			MyPort_SendStr("Time Reset");
			MyPort_SendByte(0x0D);
			MyPort_SendByte(0x0A);
		}
		Serial_data();					
		DisplayMethod();
		if(TrainNoCount>1)				// this flag is set, when the train no displayed in two times. 
		{
			TrainNoCount=0;
			DispTypeFlag=0;
		}
		
	} 
    
}	  


