
//*****************************************************************************
//This function Writes for Move train number to FontSh array in English.
//
//Arguments: nil
//
//Return:    nil
//******************************************************************************
void TrainNoDisp(void)
{
	FontCount=0;
	Slogonindex=0;											// Starting index


	while(Train_No[Slogonindex]!='~')						// Read train number  upto '~'
  	{
		
		FontSh[FontCount++]=Train_No[Slogonindex++];		// transfer the data
												 
	}
	InitDisp(FontCount); 									// Pass the FontCount value to InitDisp function 

}

//*****************************************************************************
//This function Writes for Move date/time to FontSh array in English.
//
//Arguments: nil
//
//Return:    nil
//******************************************************************************
void DateTimeDisp (void)
{
	FontCount=0;
	Slogonindex=0;
	date_flag=1;

	FontSh[FontCount++] ='T';								// Transfer TIME to the FontSh array
	FontSh[FontCount++] ='I';
	FontSh[FontCount++] ='M';
	FontSh[FontCount++] ='E';
	FontSh[FontCount++] =' ';
	FontSh[FontCount++] ='-';
	FontSh[FontCount++] =' ';
	for(Slogonindex=0;Slogonindex<5;Slogonindex++)
	{
		FontSh[FontCount++] = Date_Time[Slogonindex];

	}
	FontSh[FontCount++] =' ';
	FontSh[FontCount++] =' ';
	FontSh[FontCount++] =' ';
	FontSh[FontCount++] =' ';

	FontSh[FontCount++] ='D';							// Transfer DATE to the FontSh array
	FontSh[FontCount++] ='A';
	FontSh[FontCount++] ='T';
	FontSh[FontCount++] ='E';
	FontSh[FontCount++] =' ';
	FontSh[FontCount++] ='-';
	FontSh[FontCount++] =' ';

	
	for(Slogonindex=10;Slogonindex<19;Slogonindex++)
	{
		FontSh[FontCount++] = Date_Time[Slogonindex];
	}
InitDisp(FontCount);
			
}
//*****************************************************************************
//This function Writes for Move English station name to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void EngStationName(void)
{

	FontCount=0;
	Slogonindex=0;												// Starting index

MyPort_SendByte(0X0d);
MyPort_SendByte(0X0A);
	while(Eng_Sta_Name[Slogonindex]!='~')						// Read train number  upto '~'
  	{
			
			SloganLetter=Eng_Sta_Name[Slogonindex++];			// Get single index from array
			FontSh[FontCount++]=SloganLetter;
			MyPort_SendByte(SloganLetter);						// Char value move to array
	}
	Slogonindex=0;												// Starting index

	while(pgm_read_byte(&AtWelE[Slogonindex])!='~')				// Read slogon english array 0 data from program memory upto '*'
  	{
		
		SloganLetter=pgm_read_byte(&AtWelE[Slogonindex++]);		// Get single index from array
		FontSh[FontCount++]=SloganLetter;
		MyPort_SendByte(SloganLetter);															// Char value move to array
	}
	InitDisp(FontCount); 										// Pass the FontCount value to InitDisp function 

	
}

//*****************************************************************************
//This function Writes for Move English train no to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void EngTrainNumberDisp(void)
{

	FontCount=0;
	Slogonindex=0;													// Starting index

	while(pgm_read_byte(&TrNOE[Slogonindex])!='~')				// Read slogon 
  	{
		
		SloganLetter=pgm_read_byte(&TrNOE[Slogonindex++]);		// Get single index from array
		FontSh[FontCount++]=SloganLetter;
																	// Char value move to array
	}
	Slogonindex=0;													// Starting index
	while(Train_No[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
		FontSh[FontCount++]=Train_No[Slogonindex++];		// Get single index from array
		//=SloganLetter;
																	// Char value move to array
	}


	
	InitDisp(FontCount); 										// Pass the FontCount value to InitDisp function 

	
}

//*****************************************************************************
//This function Writes for Move Hindi station name to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void HindStationName(void)
{

	FontCount=0;
	Slogonindex=0;													// Starting index


	while(Hind_Sta_Name[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
		FontSh[FontCount++]=Hind_Sta_Name[Slogonindex++];		// Get single index from array
		//=SloganLetter;
																	// Char value move to array
	}
	Slogonindex=0;													// Starting index
	
	while(pgm_read_byte(&AtWelH[Slogonindex])!='~')				// Read slogon english array 0 data from program memory upto '*'
  	{
		
		SloganLetter=pgm_read_byte(&AtWelH[Slogonindex++]);		// Get single index from array
		FontSh[FontCount++]=SloganLetter;
																	// Char value move to array
	}
	InitDisp(FontCount); 										// Pass the FontCount value to InitDisp function 

	
}
//*****************************************************************************
//This function Writes for Move Hindi train no to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void HindTrainNumberDisp(void)
{

	FontCount=0;
	Slogonindex=0;													// Starting index

	while(pgm_read_byte(&TrNOH[Slogonindex])!='~')				// Read slogon 
  	{
		
		SloganLetter=pgm_read_byte(&TrNOH[Slogonindex++]);		// Get single index from array
		FontSh[FontCount++]=SloganLetter;
																	// Char value move to array
	}
	Slogonindex=0;													// Starting index
	FontSh[FontCount++]=0xAA;
	while(Train_No[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
		FontSh[FontCount++]=Train_No[Slogonindex++];		// Get single index from array
		//=SloganLetter;
																	// Char value move to array
	}


	
	InitDisp(FontCount); 										// Pass the FontCount value to InitDisp function 

	
}

//*****************************************************************************
//This function Writes for Move Telugu station name to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void TeluStationName(void)
{

	FontCount=0;
	Slogonindex=0;													// Starting index


	while(Telu_Sta_Name[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
		FontSh[FontCount++]=Telu_Sta_Name[Slogonindex++];		// Get single index from array
		//=SloganLetter;
																	// Char value move to array
	}
	Slogonindex=0;													// Starting index

	while(pgm_read_byte(&AtWelT[Slogonindex])!='~')				// Read slogon english array 0 data from program memory upto '*'
  	{
		
		SloganLetter=pgm_read_byte(&AtWelT[Slogonindex++]);		// Get single index from array
		FontSh[FontCount++]=SloganLetter;
																	// Char value move to array
	}
	InitDisp(FontCount); 										// Pass the FontCount value to InitDisp function 

	
}
//*****************************************************************************
//This function Writes for Move Telugu train no to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void TeluTrainNumberDisp(void)
{

	FontCount=0;
	Slogonindex=0;													// Starting index

	while(pgm_read_byte(&TrNOT[Slogonindex])!='~')				// Read slogon 
  	{
		
		SloganLetter=pgm_read_byte(&TrNOT[Slogonindex++]);		// Get single index from array
		FontSh[FontCount++]=SloganLetter;
																	// Char value move to array
	}
	Slogonindex=0;													// Starting index
	FontSh[FontCount++]=0x0F;
	FontSh[FontCount++]=0xA0;
	while(Train_No[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
		FontSh[FontCount++]=Train_No[Slogonindex++];		// Get single index from array
		//=SloganLetter;
																	// Char value move to array
	}


	
	InitDisp(FontCount); 										// Pass the FontCount value to InitDisp function 

	
}

//*****************************************************************************
//This function Writes for Move English next station name to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void NextEngStationName(void)
{

	FontCount=0;
	Slogonindex=0;													// Starting index


	while(Eng_Sta_Name[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
		SloganLetter=Eng_Sta_Name[Slogonindex++];		// Get single index from array
		 FontSh[FontCount++]=SloganLetter;
//MyPort_SendByte(SloganLetter);
		//=SloganLetter;
																	// Char value move to array
	}
	Slogonindex=0;
	 FontSh[FontCount++]=' ';													// Starting index
	//	MyPort_SendStr(" KM ");
	while(KmArr[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
		SloganLetter=KmArr[Slogonindex++];		// Get single index from array
		FontSh[FontCount++]=SloganLetter;
	//	MyPort_SendByte(SloganLetter);															// Char value move to array
	}
	Slogonindex=0;	
//	MyPort_SendStr(" KM Prog ");
	while(pgm_read_byte(&KME[Slogonindex])!='~')				// Read slogon english array 0 data from program memory upto '*'
  	{
		
		SloganLetter=pgm_read_byte(&KME[Slogonindex++]);		// Get single index from array
		FontSh[FontCount++]=SloganLetter;
		//	MyPort_SendByte(SloganLetter);														// Char value move to array
	}
	InitDisp(FontCount); 										// Pass the FontCount value to InitDisp function 

//	MyPort_SendByte(SloganLetter);
}
//*****************************************************************************
//This function Writes for Move English Message to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void EngMsgDisp(void)
{

	FontCount=0;
	Slogonindex=0;													// Starting index


	while(Eng_Msg[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
		FontSh[FontCount++]=Eng_Msg[Slogonindex++];		// Get single index from array
		//=SloganLetter;
																	// Char value move to array
	}
	
	InitDisp(FontCount); 										// Pass the FontCount value to InitDisp function 

	
}

//*****************************************************************************
//This function Writes for move the Hindi next station name to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void NextHindStationName(void)
{

	FontCount=0;
	Slogonindex=0;													// Starting index


	while(Hind_Sta_Name[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
		FontSh[FontCount++]=Hind_Sta_Name[Slogonindex++];		// Get single index from array
		//=SloganLetter;
																	// Char value move to array
	}
	Slogonindex=0;	
	FontSh[FontCount++]=0;
		FontSh[FontCount++]=0xAA;
	while(KmArr[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
		FontSh[FontCount++]=KmArr[Slogonindex++];		// Get single index from array
		//=SloganLetter;
																	// Char value move to array
	}

	Slogonindex=0;													// Starting index
	FontSh[FontCount++]=0xAB;
	while(pgm_read_byte(&KMH[Slogonindex])!='~')				// Read slogon english array 0 data from program memory upto '*'
  	{
		
		SloganLetter=pgm_read_byte(&KMH[Slogonindex++]);		// Get single index from array
		FontSh[FontCount++]=SloganLetter;
																	// Char value move to array
	}
	InitDisp(FontCount); 										// Pass the FontCount value to InitDisp function 

	
}

//*****************************************************************************
//This function Writes for move Hindi message to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void HindMsgDisp(void)
{

	FontCount=0;
	Slogonindex=0;													// Starting index

	
	while(Hind_Msg[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
		FontSh[FontCount++]=Hind_Msg[Slogonindex++];		// Get single index from array
		//=SloganLetter;
																	// Char value move to array
	}


	
	InitDisp(FontCount); 										// Pass the FontCount value to InitDisp function 

	
}

//*****************************************************************************
//This function Writes for move Telugu station name to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void NextTeluStationName(void)
{

	FontCount=0;
	Slogonindex=0;													// Starting index


	while(Telu_Sta_Name[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
	
	    SloganLetter=Telu_Sta_Name[Slogonindex++];		// Get single index from array
		FontSh[FontCount++]=SloganLetter;
	//	MyPort_SendByte(SloganLetter);															// Char value move to array
	}
	Slogonindex=0;
	FontSh[FontCount++]=0;
	FontSh[FontCount++]=0;
														// Starting index
	FontSh[FontCount++]=0x0F;
	FontSh[FontCount++]=0xA0;
	while(KmArr[Slogonindex]!='~')				// Read train number  upto '~'
  	{
		
		SloganLetter=KmArr[Slogonindex++];		// Get single index from array
		//=SloganLetter;
			FontSh[FontCount++]=SloganLetter;
		//MyPort_SendByte(SloganLetter);																// Char value move to array
	}

	Slogonindex=0;													// Starting index
	FontSh[FontCount++]=0x0F;
	FontSh[FontCount++]=0xA1;

	while(pgm_read_byte(&KMT[Slogonindex])!='~')				// Read slogon english array 0 data from program memory upto '*'
  	{
		
		SloganLetter=pgm_read_byte(&KMT[Slogonindex++]);		// Get single index from array
		FontSh[FontCount++]=SloganLetter;
		//MyPort_SendByte(SloganLetter);
																	// Char value move to array
	}
	InitDisp(FontCount); 										// Pass the FontCount value to InitDisp function 

	
}
//*****************************************************************************
//This function Writes for Move Telugu message to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void TeluMsgDisp(void)
{

	FontCount=0;
	Slogonindex=0;													// Starting index


	while(Telu_Msg[Slogonindex]!=0xFF)				// Read train number  upto '~'
  	{
		
		FontSh[FontCount++]=Telu_Msg[Slogonindex++];		// Get single index from array
		//=SloganLetter;
																	// Char value move to array
	}


	
	InitDisp(FontCount); 										// Pass the FontCount value to InitDisp function 

	
}
//*****************************************************************************
//This function Writes for move "WISH YOU A HAPPY JOURNEY" to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void Slogan(void)
{

	Slogonindex=0;													// Starting index				
	FontCount=0;
	while(pgm_read_word(&Eng_Slog[Slogonindex])!='~')				// Read slogon english array 0 data from program memory upto '~'
  	{
		SloganLetter=pgm_read_word(&Eng_Slog[Slogonindex++]);		// Get single index from array
		FontSh[FontCount++]=SloganLetter;							// Getting  values move to the FontSh[] array.	
	}
	InitDisp(FontCount);

}
//*****************************************************************************
//This function Writes for move "SOUTH CENTRAL RAILWAYS WELCOMES YOU" to FontSh array .
//
//Arguments: nil.
//
//Return:    nil
//******************************************************************************
void Railway_Display(void)
{


	Lang=0;
	DispTypeFlag=0;
	Slogonindex=0;													// Starting index				
	FontCount=0;
	while(pgm_read_word(&Rail_Slog[Slogonindex])!='~')				// Read slogon english array 0 data from program memory upto '*'
  	{
		SloganLetter=pgm_read_word(&Rail_Slog[Slogonindex++]);		// Get single index from array
		FontSh[FontCount++]=SloganLetter;							// Getting  values move to the FontSh[] array.	
	}


	InitDisp(FontCount);

}

