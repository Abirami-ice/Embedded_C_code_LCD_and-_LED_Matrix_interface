


WORD Back_Join_Letters_Algorithm(WORD JoinLetter,WORD ColCtr)
{
	BYTE indexChange=0;	
//	DebugPort_SendByte('B');
	//		DebugPort_SendByte(ColCtr+0x30);

		if(JoinLetter!=64)	
		{
			ColCtr = ColCtr -5;                                                 //  Decrease the Disparray colctr value upto 5 values
			indexChange = 0;
			joinindex = 0;
			while(pgm_read_word(&Hindi[JoinLetter][indexChange]) != 0x8888)
			{
				Chr = pgm_read_word(&Hindi[JoinLetter][indexChange++]);               //  Get the joinletter index
			
				if(joinindex<5)													//  Upto 4 values 'OR' the joinletter value with disparray value, after that send the joinletter value itself 
				{
					Chr1 = DispArray[ColCtr];                    //  get the values from the disparray
					Chr = Chr | Chr1;                           //   OR the joinletter value and disparray value
					joinindex++;

				}
				DispArray[ColCtr++] = Chr;                                     // Send that value to disparray
			}
		}
		else
		{
			ColCtr1 = ColCtr;													//     Store the Column counter value
			ColCtr--;															//    At last colctr value is incremented and stopped so we decrement once to get the last value of disparray
			IncrementCount = 0;
		//	breakFlag=0;
		//	breakCount=0;
			do 																	//    This loop is used to identify the point where the joint will meet the letter
			{
				Chr = DispArray[ColCtr--];
				Chr1 = (BYTE) Chr;
				IncrementCount++;
				if(IncrementCount>10)
				{
					break;
				}
				                                              //  Incrementcount will store the meeting point
			}
			while( ((Chr1 < 0x77) && (Chr1<0x80)) || ((Chr1 < 0xF7) && (Chr1 < 0xFF)));           

		//	while((Chr1 != 0xF8) && (Chr1 != 0x78));

					Chr = DispArray[ColCtr];									// At the point of meeting we have to join the letters so we have to OR with some values to get the desired output
					Chr = Chr | 0x0006;
					DispArray[ColCtr++] = Chr;
					Chr = DispArray[ColCtr];
					Chr = Chr | 0x0007;
					DispArray[ColCtr++] = Chr;
					if(IncrementCount < 3)                                     //   For some letters this join doesn't shown clearly in the display so for that we have to increment the width of the joining
					{
					//	DebugPort_SendByte('S');
						DispArray[ColCtr++] = 0x001B;                          //    To increase the width add this value
						DispArray[ColCtr++] = 0x001B;
						DispArray[ColCtr++] = 0x001B;
					}

			while(ColCtr < ColCtr1)                  //    To draw a line above the letter, we have to add 0x0003 with disparray values                 
			{
				Chr = DispArray[ColCtr];			 
				Chr = Chr | 0x0003;
				DispArray[ColCtr++] = Chr;
			}
	
			ColCtr = ColCtr-1;                                
			Chr = DispArray[ColCtr];                    //   To change the last value of colctr we use this
			Chr = Chr ^ 0x0001;
			Chr = Chr | 0x0004;
			DispArray[ColCtr++] = Chr;
	
			indexChange=0;
			while(pgm_read_word(&Hindi[JoinLetter][indexChange])!=0x8888)         // add the join letter 
			{		
					//DebugPort_SendByte('4');
					Chr1=pgm_read_word(&Hindi[JoinLetter][indexChange]);
					DispArray[ColCtr++]=Chr1;
					indexChange++;
			}
		}
	return ColCtr;
}




WORD Top_Join_Letters_Algorithm(WORD JoinLetter,WORD ColCtr)
{
		
	BYTE indexChange=0;

		ColCtr1 = ColCtr;										//     Store the Column counter value
	//	DebugPort_SendByte(ColCtr1+0x30);
		ColCtr--;    											//    At last colctr value is incremented and stopped so we decrement once to get the last value of disparray                                            
	
	//		DebugPort_SendByte('W');
			do 												    //    This loop is used to identify the point where the joint will meet the letter
			{
				Chr = DispArray[ColCtr--];
				Chr1 = (BYTE) Chr;
		//		DebugPort_SendByte('W');
			}
			while( ((Chr1 < 0x77) && (Chr1<0x80)) || ((Chr1 < 0xF7) && (Chr1 < 0xFF)));
		//	while((Chr1 != 0xF8) && (Chr1 != 0x78) && (Chr1 != 0xFC) && (Chr1 != 0x7C));
		//  while((Chr1< 0xF6) && (Chr1 < 0xFF));
			ColCtr = ColCtr - 5;                               //   After finding the point decrease the colctr upto 5 values

	
		indexChange=0;
		while(pgm_read_word(&Hindi[JoinLetter][indexChange])!=0x8888)   //  Join the joinletter value with disparray values 
		{
				Chr1=pgm_read_word(&Hindi[JoinLetter][indexChange]);
				if(ColCtr >= ColCtr1)                               //  If the joinletter value exceed the previous colctr then we have to add 0x0018
				{
			//		DebugPort_SendByte('4');
					Chr = Chr1 | 0x0018;
				}	
				else
				{
				//	DebugPort_SendByte('5');						// Get the values from the disparray
					Chr = DispArray[ColCtr];
				}
			
				Chr = Chr | Chr1;									//  OR the disparray values with the joinletter value
				
				DispArray[ColCtr++]=Chr;
				indexChange++;
		}
		if(ColCtr < ColCtr1)              //  If the current colctr value doesn't exceed the previous colctr then, we have to shift the previous colctr to the current value 
		{
		//	DebugPort_SendByte('6');
			ColCtr = ColCtr1;
		}

return ColCtr;

}

WORD Bottom_Join_Letters_Algorithm(WORD JoinLetter,WORD MainLetter,WORD ColCtr)
{
	BYTE indexChange=0;

			ColCtr = ColCtr - DecreaseColctr ;                 //    TO REDUCE THE COLCTR OF MAINLETTER, BECOZ IT FORMS A SINGLE LETTER
			index1 = 0;
			if(((JoinLetter==65) || (JoinLetter==66)) && ((MainLetter == 48) || (MainLetter == 49)) && (RaDown == 0))               //	For Ra and RRa it will create a new letter so we pass the index		
			{
				if(MainLetter == 48)
					MainLetter = JoinLetter + 190;                 // TO GET 255, 256
				else if(MainLetter == 49)
					MainLetter = JoinLetter + 192;


				while(pgm_read_word(&Hindi[MainLetter][index1])!=0x8888)  //main letter loop
				{
					Chr=pgm_read_word(&Hindi[MainLetter][index1++]);
					DispArray[ColCtr++]=Chr;
				}

			}
			else if((JoinLetter == 67) && ((MainLetter == 38) || (MainLetter == 57)))            //   For HA and DA it will create a new letter so we have to pass the index
			{
				if(MainLetter == 38)
					MainLetter = 259;
				else if(MainLetter == 57)
					MainLetter = 260;

				while(pgm_read_word(&Hindi[MainLetter][index1])!=0x8888)  //main letter loop
				{
					Chr=pgm_read_word(&Hindi[MainLetter][index1++]);
					DispArray[ColCtr++]=Chr;
				}
			}
			else
			{
				ColCtr = ColCtr + DecreaseColctr ;           //  THERE IS NO NEED TO INCREASE THE COLCTR, SO INCREMENT IT
				ColCtr1 = ColCtr;                            //  Store the colctr value
				ColCtr--;                                    //  to get the last value of disparray
				do 
				{											 //  To determine the meeting point
					Chr = DispArray[ColCtr--];
					Chr1 = (BYTE) Chr;
				}
			while( ((Chr1 < 0x77) && (Chr1<0x80)) || ((Chr1 < 0xF7) && (Chr1 < 0xFF)));
			//	while((Chr1 != 0xF8) && (Chr1 != 0x78));

					
				if(Chr1 == 0x78)                           //   to change the meeting point for small letters i.e letters which has short colctr
					ColCtr = ColCtr -6;
				else
					ColCtr = ColCtr -4;											
				indexChange=0;
				while(pgm_read_word(&Hindi[JoinLetter][indexChange])!=0x8888)     //    add the joinletter value with disparray value
				{
					Chr1=pgm_read_word(&Hindi[JoinLetter][indexChange]);
				
					if(ColCtr >= ColCtr1)								//  If the joinletter value exceed the previous colctr then we have to add 0x0018							
						Chr = Chr1 | 0x0018;
					else
						Chr = DispArray[ColCtr];
				
					Chr = Chr | Chr1;
					DispArray[ColCtr++]=Chr;
					indexChange++;
				}
				if(ColCtr<ColCtr1)                     //  If the current colctr value doesn't exceed the previous colctr then, we have to shift the previous colctr to the current value 
				{
					ColCtr = ColCtr1;              
				}
		}

return ColCtr;

}

WORD  Front_Join_Algorithm(WORD  JoinLetter,WORD MainLetter,WORD ColCtr)
{
    
	IncrementCount = 0;											
	joinindex = 0;
		ColCtr1 = ColCtr;										//     Store the Column counter value
		ColCtr = ColCtr - 1;									//    To get the last value of disparray				
		do 														//    This loop is used to identify the point where the joint will meet the letter
		{
			Chr = DispArray[ColCtr--];
			Chr1 = (BYTE) Chr;
			IncrementCount++;                                    //  Incrementcount will store the meeting point
		}
		while( ((Chr1 < 0x77) && (Chr1<0x80)) || ((Chr1 < 0xF7) && (Chr1 < 0xFF)));
	//	while((Chr1 != 0xF8) && (Chr1 != 0x78));


		joinindex = DecreaseColctr - IncrementCount;              //   DecreaseColctr mention the last letter's colctr, to determine the meeting point we have to subtract the increment value from DecreaseColctr

		ColCtr = ColCtr1 - DecreaseColctr;						  //   To decrement the colctr

		DispArray[ColCtr++] = 0x0018;                              //  add the first four values of join letter to the disparray
		DispArray[ColCtr++] = 0x1FFC;
		DispArray[ColCtr++] = 0x1FFE;
		DispArray[ColCtr++] = 0x001B;
			
		CheckFlag = 0;												//  add the mainletter
		index1 = 0;
		while(pgm_read_word(&Hindi[MainLetter][index1])!=0x8888)
		{
			Chr = pgm_read_word(&Hindi[MainLetter][index1++]);
		
			if(CheckFlag == 1)										//   third step simply add the remaining values of mainletter 
			{
			//	DebugPort_SendByte('1');
				DispArray[ColCtr++] = Chr;
			}
			else if(index1 < joinindex)								//   first step add 0x0003 upto the meeting point we already find
			{
			//	DebugPort_SendByte('2');
				Chr = Chr | 0x0003;
				DispArray[ColCtr++] = Chr;

			}
			else													// second step we add the finishing point of join letter with the meeting point
			{
			//	DebugPort_SendByte('3');
				CheckFlag = 1;
				Chr = Chr | 0x0006;
				DispArray[ColCtr++] = Chr;
				Chr = pgm_read_word(&Hindi[MainLetter][index1++]);
				Chr = Chr | 0x0004;
				DispArray[ColCtr++] = Chr;
			}
			//**********		Change by ambro		*******************************
			Chr = pgm_read_word(&Hindi[MainLetter][index1+1]);
			if (Chr==0x8888 && CheckFlag==0)
			{
				ColCtr=ColCtr-2;
				index1=index1-2;
				Chr = pgm_read_word(&Hindi[MainLetter][index1++]);
				Chr = Chr | 0x0006;
				DispArray[ColCtr++] = Chr;
				Chr = pgm_read_word(&Hindi[MainLetter][index1++]);
				Chr = Chr | 0x0004;
				DispArray[ColCtr++] = Chr;
				break;
			}
			//****************************************************************************
		}
				


	return ColCtr;
}


WORD RaJoin(WORD ColCtr)                   // THIS FUNCTION IS USED TO DRAW A LINE ABOVE THE LETTER WHICH IS LASTLY PRESENT IN THE DISPARRAY
{                                            //  RA + HAL+ KA

		ColCtr1 = ColCtr;    				//     Store the Column counter value                
		ColCtr = ColCtr - 1;                 //    To get the last value of disparray				
		IncrementCount = 0;
		do 									//    This loop is used to identify the point where the joint will meet the letter
		{
		//	DebugPort_SendByte('2');
			Chr = DispArray[ColCtr--];
			Chr1 = (BYTE) Chr;
			IncrementCount++;                // Increment count refers the point that in which column it is present in the disparray
		}
		//while((Chr1 != 0xF8) && (Chr1 != 0x78));
		while( ((Chr1 < 0x77) && (Chr1<0x80)) || ((Chr1 < 0xF7) && (Chr1 < 0xFF)));


		ColCtr = ColCtr1 - IncrementCount;         //  To start our joint from the calculated position
		ColCtr = ColCtr -2;							// start before two points


		Chr = DispArray[ColCtr];                     //  Get values from the disparray
		DispArray[ColCtr++] = Chr | 0x0002;          //  Or the join letter value with the disparray value and store it in the disparray
		Chr = DispArray[ColCtr];
		DispArray[ColCtr++] = Chr | 0x0007;
		Chr = DispArray[ColCtr];
		DispArray[ColCtr++] = Chr | 0x0005;
		Chr = DispArray[ColCtr];
		DispArray[ColCtr++] = Chr | 0x0001;


		if(ColCtr1 > ColCtr)
		{
			ColCtr = ColCtr1;                        // Restore the colctr value
		}

	return ColCtr;


}

WORD DoubleJoin_Algorithm(WORD Uniqueletter, WORD JoinLetter,WORD MainLetter, WORD ColCtr)
{
	ch1 = FontSh[Temp1+2];
//	ch2 = FontSh[Temp1+4];

	Temp1 = Temp1 +1;                                     //   If a single letter forms from joining two letters then we have to increment the count
	HalfLetterFlag = 1;                                   //   Identification of forming single letter before a new join 
	FrontjoinFlag = 1;                                   //    Front join is differ for forming single letters from double joining and half letters from double joining, to identify the difference we use this flag

	 if((Uniqueletter==0x15 && MainLetter==0x24))		// ka+hal+ta 	//HAL=0x4D
	 {
		Uniqueletter = 240;
	 }
	 else if((Uniqueletter==0x26 && MainLetter==0x26)) //da+hal+da
	 {
		Uniqueletter = 241;
	 }
	 //***************			Change by ambro			***********************
	/* else if((Uniqueletter==0x24 && MainLetter==0x24))//ta+hal+ta
	 {
		Uniqueletter = 242;
	 }*/
	 //*****************************************************************************
	 else if((Uniqueletter==0x15 && MainLetter==0x37))	//ka+hal+SSA
	 {
		Uniqueletter = 265;
	 }
	 else if((Uniqueletter == 0x1C && MainLetter == 0x1E))	// ja+Hal+nya
	 {
		Uniqueletter = 254;
	
	 }
	 else if((Uniqueletter == 0x39 && MainLetter == 0x2E))	//HA+hal+MA
	 {
		Uniqueletter = 261;
	 }
	 else if((Uniqueletter==0x16 && MainLetter==0x28))	     //  kha + hal + na	
	 {
		Uniqueletter = 266;
	 }
	 else if((Uniqueletter==0x19 && MainLetter==0x2E))		//  nga + hal + ma
	 {
		Uniqueletter = 267;
	 }
	 else if((Uniqueletter==0x24 && MainLetter==0x28))	     //  ta + hal + na	
	 {
		Uniqueletter = 268;
	 }
	 else if((Uniqueletter==0x2A && MainLetter==0x24))       //  pa + hal + ta		
	 {
		Uniqueletter = 269;
	 }
	 else if((Uniqueletter==0x37 && MainLetter==0x1F))	      // SSA  + hal + tta	
	 {
		Uniqueletter = 270;
	 }
	 else if((Uniqueletter==0x37 && MainLetter==0x20))		// SSA  + hal + ttha	
	 {
		Uniqueletter = 271;
	 }
	 else if ((Uniqueletter == 0x39) && ((MainLetter == 0x23) || (MainLetter == 0x28) || (MainLetter == 0x2F) || (MainLetter == 0x32)|| (MainLetter == 0x35)))        // COMBINATIONS OF HA with (nna, na, ya, la, va)
	 {
	 	for(i=0;i<5;i++)
		{
			//GSMPort_SendByte('Q');
			if(Valarr1[i] == MainLetter)                          //  It will choose the index
			{
				Uniqueletter = i+272;
				break;
			}
		}
	 }
	 else if ((Uniqueletter == 0x36) && ((MainLetter == 0x35) || (MainLetter == 0x28) || (MainLetter == 0x1A) || (MainLetter == 0x32)) )        // COMBINATIONS OF sha with (va, na, ca, la)
	 {
	 	for(i=0;i<5;i++)
		{
		//	GSMPort_SendByte('Q');
			if(Valarr2[i] == MainLetter)
			{
				Uniqueletter = i+277;
				break;
			}
		}

	 }
	 else if(Uniqueletter == 0x30)								//  ra + consonants
	 {
	 //	DebugPort_SendByte('E');
		index1 = 0;
		DecreaseColctr = 0;
		while(pgm_read_word(&Hindi[MainLetter][index1])!=0x8888)
		{
			Chr = pgm_read_word(&Hindi[MainLetter][index1++]);
			DispArray[ColCtr++] = Chr;
			DecreaseColctr = index1;
		}
		if(ch1 == 0x3F)   											// next letter is front join then call front join                           
		{
			Temp1 = Temp1 + 1;
			ColCtr = Front_Join_Algorithm(ch1,MainLetter,ColCtr);
		}
		else if((ch1 == 0x3E) || (ch1 == 0x40) || ((ch1 > 0x48) && (ch1 < 0x4D)) )     //  next letter is back join then call back join
		{
				//		DebugPort_SendByte('H');

			Temp1 = Temp1 + 1;
			ColCtr = Back_Join_Letters_Algorithm(ch1,ColCtr);
		}


		RaJoin(ColCtr);                                //  This function will draw an above line to create this font
		goto out;

	 }
	 else if(MainLetter==0x30)							// Consonants+Hal+RA join
	 {
		RaDown = 1;
	 	Uniqueletter = Uniqueletter + 182;

	 }
	 		//0x26 - DA, 0x2C-BA, 0x2D-BHA, 0x2E-MA, 0X2F-YA,  0x17- GA	, 0X18 -GHA, 0X27-DHA,  0X28- NA																					//0x2D,0x17,0x18,0x27,0x2E,0x28,0x2F														
	 else if((Uniqueletter==0x26) && (((MainLetter>=0x2C) && (MainLetter<=0x2F)) || (MainLetter==0x17) || (MainLetter==0x18) || (MainLetter==0x27)  || (MainLetter==0x28) || (MainLetter==0x35) ))                // combinations of da with (ba, bha, ma ,ya, ga, gha, dha, na, va)
	 {
	 	for(i=0;i<10;i++)
		{
		//	GSMPort_SendByte('Q');
			if(Valarr[i] == MainLetter)
			{
				Uniqueletter = i+244;
				break;
			}
		}
	 }
	 else				//  Consonants+Hal+Consonants                //   Forming half letters while joining two letters
	 {
		FrontjoinFlag = 0;                                 
	 	HalfLetterFlag = 0;
	 	Temp1 = Temp1 - 1;
		Uniqueletter = Uniqueletter + 108;                 ///  TO REACH THE STARTING PLACE OF 129	
	 }

	index1 = 0;
	DecreaseColctr = 0;

	while(pgm_read_word(&Hindi[Uniqueletter][index1]) != 0x8888)  //main letter loop
	{
		Chr = pgm_read_word(&Hindi[Uniqueletter][index1++]);
		DispArray[ColCtr++] = Chr;
		DecreaseColctr = index1;
		//FrontJoinCounter = index1;                             //    This is for front join function while multiple hal occurs
	}


	if(ch1 == 0x3F)
	{
		if(FrontjoinFlag==1)						//    for double letter join into single letter
		{
		//	DebugPort_SendByte('J');                 
			Temp1 = Temp1 +1;                       //   
			ColCtr = Front_Join_Algorithm(ch1,Uniqueletter,ColCtr);
		}
		else										//     for half letter forming while two letters join together
		{
			Temp1 = Temp1 +2;
			ColCtr = Front_Join_Algorithm(ch1,Uniqueletter,ColCtr);
			index1 =0;
			while(pgm_read_word(&Hindi[MainLetter][index1]) != 0x8888)  //main letter loop
			{
				Chr = pgm_read_word(&Hindi[MainLetter][index1++]);
				DispArray[ColCtr++] = Chr;
				DecreaseColctr = index1;
			}
		}
	}


	out:
		i=0;

	return ColCtr;


}

WORD SingleDoubleLetter_Algorithm(WORD Uniqueletter, WORD MainLetter, WORD ColCtr)             //  This function is used for forming different letters while continuously hal comes
{

	ch1 = FontSh[Temp1+1];
	ch2 = 0;

		if(MainLetter == 0x30)                          /// FOR RA       //   MAINLETTER = FONSH-1
		{
		//	DebugPort_SendByte('R');
			Uniqueletter1 = Uniqueletter;					//  index passing while before ra is the last value				
			Uniqueletter = Uniqueletter+145;                 ///   UNIQUELETTER = FONTSH -3
		}
		else if(Uniqueletter == 0x30)
		{
		//	DebugPort_SendByte('W');
			ch2 = Uniqueletter;                              //  index passing while before ra is the third value before hal
			Uniqueletter = MainLetter + 108;
		}
		else if(MainLetter == 0x24)
		{
			if(Uniqueletter == 0x15)
			{
				Uniqueletter = 129;                                            //  THIS IS FOR HALF KA
				index1=0;
				while(pgm_read_word(&Hindi[Uniqueletter][index1])!=0x8888)  //main letter loop
				{
					Chr=pgm_read_word(&Hindi[Uniqueletter][index1++]);
					DispArray[ColCtr++]=Chr;
					//FrontJoinCounter = index1;
				}

				Uniqueletter = 144;                         //  THIS IS FOR HALF THA

			}
			else if(Uniqueletter == 0x24)
				Uniqueletter = 243;
			else if(Uniqueletter == 0x2A)
				Uniqueletter = 283;
		}
		else if(((Uniqueletter == 0x26) && ( MainLetter != 0x2E)) || ((Uniqueletter == 0x39) && (MainLetter == 0x2E)) || ((Uniqueletter == 0x19) && (MainLetter == 0x2E))|| ((Uniqueletter == 0x37) && ((MainLetter == 0x1F) || (MainLetter == 0x20))) || ((Uniqueletter == 0x39) && ((MainLetter == 0x23) || (MainLetter == 0x28) || (MainLetter == 0x2F) || (MainLetter == 0x32) || (MainLetter == 0x35))))
		{
		//	Uniqueletter = 146;                   //  THIS IS FOR HALF THA
			Uniqueletter = Uniqueletter + 108;
			index1=0;
			while(pgm_read_word(&Hindi[Uniqueletter][index1])!=0x8888)  //main letter loop
			{
				Chr=pgm_read_word(&Hindi[Uniqueletter][index1++]);
				DispArray[ColCtr++]=Chr;
				//FrontJoinCounter = index1;

			}

			Uniqueletter = MainLetter + 108;                         //  THIS IS FOR ANOTHER HALF LETTER

		}
/*		else if((Uniqueletter == 0x39) && (MainLetter == 0x2E))
		{
			Uniqueletter = 165;                   //  THIS IS FOR HALF HA
			index1=0;
			while(pgm_read_word(&Hindi[Uniqueletter][index1])!=0x8888)  //main letter loop
			{
				Chr=pgm_read_word(&Hindi[Uniqueletter][index1++]);
				DispArray[ColCtr++]=Chr;
				//FrontJoinCounter = index1;
			}

			Uniqueletter = MainLetter + 108;                         //  THIS IS FOR ANOTHER HALF LETTER

		}*/
		else if((Uniqueletter == 0x15) && (MainLetter == 0x37))       // before ka + hal + ssa come means then   
		{
			Uniqueletter = 262;
		}
		else if((Uniqueletter == 0x1C) && (MainLetter == 0x1E))        // before ja + hal + nya
		{
			Uniqueletter = 263;
		}
		else if((Uniqueletter == 0x26) && ( MainLetter == 0x2E))       // before da + hal + ma
		{
			Uniqueletter = 264;
		}
		else if((Uniqueletter == 0x16) && ( MainLetter == 0x28))       // before kha + hal + na
		{
			Uniqueletter = 281;
		}
		else if((Uniqueletter == 0x24) && ( MainLetter == 0x28))        // before ta + hal + na
		{
			Uniqueletter = 282;
		}
		else if ((Uniqueletter == 0x36) && ((MainLetter == 0x35) || (MainLetter == 0x28) || (MainLetter == 0x1A) || (MainLetter == 0x32)) )        // COMBINATIONS OF sha
		{
			for(i=0;i<5;i++)
			{
//				GSMPort_SendByte('Q');
				if(Valarr2[i] == MainLetter)
				{
					Uniqueletter = i+284;
					break;
				}
			}

		}
		
			index1=0;
			while(pgm_read_word(&Hindi[Uniqueletter][index1])!=0x8888)  //main letter loop
			{
				Chr=pgm_read_word(&Hindi[Uniqueletter][index1++]);
				DispArray[ColCtr++]=Chr;
				//FrontJoinCounter = index1;
			}

		if((ch2 == 0x30) || ((MainLetter ==0x30) && (Uniqueletter1 == 0x30)))
		{
		//	DebugPort_SendByte('G');
			Temp1 = Temp1 +1;
			Uniqueletter = ch1;                         //  THIS IS FOR HALF THA
			
			index1=0;
			while(pgm_read_word(&Hindi[Uniqueletter][index1])!=0x8888)  //main letter loop
			{
				Chr=pgm_read_word(&Hindi[Uniqueletter][index1++]);
				DispArray[ColCtr++]=Chr;
				//FrontJoinCounter = index1;

			}

		
			RaJoin(ColCtr);		
		}

return ColCtr;
}




void InterruptJoin(WORD TotalIndex1)
{
	BYTE indexChange=0;
	ColCtr=0;
//	MyPort_SendByte('A');
//	MyPort_SendByte('A');
//	for(Temp1=0;Temp1<TotalIndex1;Temp1++)
//	{
//		MyPort_SendByte(FontSh[Temp1]);
//	}

	for(Temp1=0;Temp1<TotalIndex1;Temp1++)
	{
		ch = FontSh[Temp1];				// 
		ch2 = FontSh[Temp1+1];			//
		ch3 = FontSh[Temp1+2];
	//	MyPort_SendByte('B');			//
	//	MyPort_SendByte(ch);

		if(ch==0xAA)
		{
	//	DebugPort_SendStr("Eng");
			Eng_Flag_Hindi=1;
		}
		else if(ch==0xAB)
		{
			Eng_Flag_Hindi=0;
		}
		else if(Eng_Flag_Hindi==1)
		{
			BYTE EngCh;
			EngCh=FontSh[Temp1];
			indexChange=0;
			while(pgm_read_word(&Eng_Font[EngCh-32][indexChange])!=0x8888)
			{
				Chr=pgm_read_word(&Eng_Font[EngCh-32][indexChange++]);
				DispArray[ColCtr]=Chr;
				//DebugPort_SendByte(DispArray[ColCtr]/256);
				//DebugPort_SendByte(DispArray[ColCtr]%256);
				ColCtr++;	
			}
			DispArray[ColCtr++] = 0;
			DispArray[ColCtr++] = 0;
	
		}
		else
		{
	
			if(Temp1 > 0)						// Previous font selection
				ch1 = FontSh[Temp1 - 1];
			
			BackJoinIndex = Back_JoinLetter_Search(ch);						// Check the letter is back join letter
	       	TopJoinIndex=Top_JoinLetter_Search(ch);							//Check the letter is Top join letter
			BottomJoinIndex=Bottom_JoinLetter_Search(ch);					//Check the letter is Bottom join letter

			if((ch == 0x4D) && (HalfLetterFlag == 1) && (ch2 !=0) && (Temp1 <= TotalIndex1))      // continuation of two letters joining function, if it forms a single letter
			{
		//		DebugPort_SendByte('g');
				// 
				HalfLetterFlag = 0;                            //    HalfLetterFlag is the identification of continuation of hal
				RaDown = 0;                                    //    RaDown flag avoids creation of new letter while consonants+ hal + ra comes
				ch4 = FontSh[Temp1 - 3];
				ColCtr = ColCtr - DecreaseColctr;
				ColCtr = SingleDoubleLetter_Algorithm(ch4,ch1, ColCtr);
			}
			else if ((ch2==0x4D) && (ch3!=0) && (Temp1 <= TotalIndex1))           //    two letters joining function
			{
		//		DebugPort_SendByte('X');
				HalfLetterFlag = 0;
				RaDown = 0;
				Temp1 = Temp1 + 1;
				ColCtr = DoubleJoin_Algorithm(ch,ch2,ch3,ColCtr);
			}
			else if(pgm_read_byte(&Back_JoinLetter_Array[BackJoinIndex]) == ch)                
			{
			//	DebugPort_SendByte('B');
				HalfLetterFlag = 0;
				RaDown = 0;
				ColCtr = Back_Join_Letters_Algorithm(ch,ColCtr);                   //  Back letter joining function
			}
			else if(pgm_read_byte(&Top_JoinLetter_Array[TopJoinIndex]) == ch)                  
			{
			//	DebugPort_SendByte('T');
				HalfLetterFlag = 0;
				RaDown = 0;
				ColCtr = Top_Join_Letters_Algorithm(ch,ColCtr);                      //   Top Letter joining function
			}
			else if(pgm_read_byte(&Bottom_JoinLetter_Array[BottomJoinIndex]) == ch)              
			{
			//	DebugPort_SendByte('U');
				HalfLetterFlag = 0;
				ColCtr = Bottom_Join_Letters_Algorithm(ch,ch1,ColCtr);              //   Bottom Letter joining function
			}
			else if(ch == 63)														// 	Front join algorithem for I sign
			{
			//	DebugPort_SendByte('F');
				HalfLetterFlag = 0;
				RaDown = 0;
				ColCtr = Front_Join_Algorithm(ch,ch1,ColCtr);                       //    Front joining function
			}
			else if((ch>0x03 && ch<0x3A) || (ch>0x57 && ch<0x62) || (ch>0x65 && ch<0x80) || (ch == 0x00) || (ch==100))               ///  CONSONANTS 21-57  // Display Consonants letters
			{
			//	DebugPort_SendByte('Z');
				HalfLetterFlag = 0;
				RaDown = 0;
				i=0;DecreaseColctr = 0;
				while(pgm_read_word(&Hindi[ch][i])!=0x8888)					// Get the values from the program memory upto 0x8888.	
				{
					Chr=pgm_read_word(&Hindi[ch][i++]);						// Read font from memory
					DecreaseColctr = i;										// To count the font column size
					DispArray[ColCtr++]=Chr;								// Column hex value move to display array
					//FrontJoinCounter = i;
				}
			}
		}

	}
//	for(i=0;i<TotalIndex1;i++)
//	{
//	    FontSh[i]=0;
//	}


}





/*
 

 //////////////// DOUBLE JOIN 


	Temp1 = Temp1 +1;
	DecreaseColctr = 0;
	 if((Uniqueletter==0x15 && MainLetter==0x24))
	 {
	 		GSMPort_SendByte('1');
		HalfLetterFlag = 1;
		Uniqueletter = 240;
		index1=0;
		while(pgm_read_word(&Hindi[Uniqueletter][index1])!=0x8888)  //main letter loop
		{
			Chr=pgm_read_word(&Hindi[Uniqueletter][index1++]);
			DispArray[ColCtr++]=Chr;
			DecreaseColctr = index1;
		}
	 }
	 else if((Uniqueletter==0x26 && MainLetter==0x26))
	 {
	 		GSMPort_SendByte('2');
		Uniqueletter = 241;
		index1=0;
		while(pgm_read_word(&Hindi[Uniqueletter][index1])!=0x8888)  //main letter loop
		{
			Chr=pgm_read_word(&Hindi[Uniqueletter][index1++]);
			DispArray[ColCtr++]=Chr;
	//		DecreaseColctr = index1;
		}
	 }
	 else if((Uniqueletter==0x24 && MainLetter==0x24))
	 {
	 		GSMPort_SendByte('3');
		HalfLetterFlag = 1;
		Uniqueletter = 242;
		index1=0;
		while(pgm_read_word(&Hindi[Uniqueletter][index1])!=0x8888)  //main letter loop
		{
			Chr=pgm_read_word(&Hindi[Uniqueletter][index1++]);
			DispArray[ColCtr++]=Chr;
			DecreaseColctr = index1;
		}
	 }
	 else if((Uniqueletter==0x15 && MainLetter==0x37))
	 {
	 		GSMPort_SendByte('3');
		HalfLetterFlag = 1;
		Uniqueletter = 253;
		index1=0;
		while(pgm_read_word(&Hindi[Uniqueletter][index1])!=0x8888)  //main letter loop
		{
			Chr=pgm_read_word(&Hindi[Uniqueletter][index1++]);
			DispArray[ColCtr++]=Chr;
			DecreaseColctr = index1;
		}
	 }
	 else if((Uniqueletter==0x1C && MainLetter==0x1E))
	 {
	 		GSMPort_SendByte('3');
		HalfLetterFlag = 1;
		Uniqueletter = 254;
		index1=0;
		while(pgm_read_word(&Hindi[Uniqueletter][index1])!=0x8888)  //main letter loop
		{
			Chr=pgm_read_word(&Hindi[Uniqueletter][index1++]);
			DispArray[ColCtr++]=Chr;
			DecreaseColctr = index1;
		}
	 }
	 else if(Uniqueletter == 0x30)
	 {
	 	HalfLetterFlag = 1;
	 }
	 else if(MainLetter==0x30)
	 {
	 			GSMPort_SendByte('4');
		HalfLetterFlag = 1;
	 	Uniqueletter = Uniqueletter + 182;
		index1=0;
		while(pgm_read_word(&Hindi[Uniqueletter][index1])!=0x8888)  //main letter loop
		{
			Chr=pgm_read_word(&Hindi[Uniqueletter][index1++]);
			DispArray[ColCtr++]=Chr;
			DecreaseColctr = index1;
		}
	 }
	 																							//0x2D,0x17,0x18,0x27,0x2E,0x28,0x2F														
	 else if((Uniqueletter==0x26) && ((MainLetter==0x2C) || (MainLetter==0x2D) || (MainLetter==0x17) || (MainLetter==0x18) || (MainLetter==0x27) || (MainLetter==0x2E) || (MainLetter==0x28) || (MainLetter==0x2F)))
	 {
	 	HalfLetterFlag = 1;
	 	for(i=0;i<9;i++)
		{
		GSMPort_SendByte('Q');
			if(Valarr[i]==MainLetter)
			{
				Value=i+244;
				break;
			}
		}
//	 	Uniqueletter = 244;                 // DA + RA
		index1=0;
		while(pgm_read_word(&Hindi[Value][index1])!=0x8888)  //main letter loop
		{
			Chr=pgm_read_word(&Hindi[Value][index1++]);
			DispArray[ColCtr++]=Chr;
	//		DecreaseColctr = index1;
		}
	 }
	 else
	 {
	 	Temp1 = Temp1 - 1;
			Uniqueletter = Uniqueletter + 108;                 ///  TO REACH THE STARTING PLACE OF 129
		 	index1 = 0;
	
			while(pgm_read_word(&Hindi[Uniqueletter][index1]) != 0x8888)  //main letter loop
			{
				Chr = pgm_read_word(&Hindi[Uniqueletter][index1++]);
				DispArray[ColCtr++] = Chr;
			}
		}
	
	return ColCtr;



*/
//    TOP JOIN

	/*	while(ColCtr>0)
		{
			DebugPort_SendByte('1');
			Chr = DispArray[ColCtr--];
			Chr1 = (BYTE) Chr;
			if((Chr1 == 0xF8) || (Chr1 == 0x78))
			{
				DebugPort_SendByte('2');
				ColCtr = ColCtr - 5;
				break;
			}
		}*/

