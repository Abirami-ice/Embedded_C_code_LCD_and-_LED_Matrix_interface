void Telugu_disp(BYTE TotalFonts)	
{
	BYTE Temp3,indexChange=0;
	NumCount=0;
	ColCtr=0;
		MyPort_SendByte(0x0d);
		MyPort_SendByte(0x0a);
	MyPort_SendByte('a');
//	DebugPort_SendByte('A');
	MyPort_SendByte((TotalFonts/10)+0x30);
	MyPort_SendByte((TotalFonts%10)+0x30);
	for(Temp3=0;Temp3<TotalFonts;Temp3++)
	{
	
//	DebugPort_SendByte('A');
//	MyPort_SendByte((Temp3/10)+0x30);
//	MyPort_SendByte((Temp3%10)+0x30);
	
		ch=( ((FontSh[Temp3]) * 256) + (FontSh[Temp3+1]) );

		ch0=( ((FontSh[Temp3+2]) * 256) + (FontSh[Temp3+3]) );	 // 2nd element of Array(mainletter)
       // ch0=TeluguFontIndex[NumCount+1];                
		
		if(ch0==1900 && ch==4000 && ch==4001 )
			ch0=0;
          
		  
		  
		if(ch==4000)
		{
			MyPort_SendByte('Y');
			Temp3++;
			Eng_Flag=1;	

		} 
		else if(ch==4001)
		{
			MyPort_SendByte('N');
			Eng_Flag=0;
		}
		else if(Eng_Flag==1)
		{
		//	DebugPort_SendStr("Eng");
		//	FirInx='A';		//(BYTE)(ch/256);
			//ch='A';
			indexChange=0;
			ch=FontSh[Temp3];
			MyPort_SendByte(ch);
	//	MyPort_SendByte('E');
			while(pgm_read_word(&Eng_Font[ch-32][indexChange])!=0x8888)
			{
				Chr=pgm_read_word(&Eng_Font[ch-32][indexChange++]);
				DispArray[ColCtr]=Chr;
				//DebugPort_SendByte(DispArray[ColCtr]/256);
				//DebugPort_SendByte(DispArray[ColCtr]%256);
				ColCtr++;	
			}
			DispArray[ColCtr++] = 0;
			DispArray[ColCtr++] = 0;	
		/*	
			
			SecInx='B';			//(BYTE)(ch%256);
			ch='B';
			DebugPort_SendByte(ch);
			index=0;
			while(pgm_read_word(&Eng_Font[ch-32][index])!=0x8888)
			{
				Chr=pgm_read_word(&Eng_Font[ch-32][index++]);
				DispArray[ColCtr]=Chr;
				//DebugPort_SendByte(DispArray[ColCtr]/256);
				//DebugPort_SendByte(DispArray[ColCtr]%256);
				ColCtr++;	
			}
			DispArray[ColCtr++] = 0;
			DispArray[ColCtr++] = 0;*/
		}
		else //if(Eng_Flag==0)
		{
	//MyPort_SendByte('T');
		
		  	if((((ch>16) && (ch<472))  ) && (ch0==1707) )  	//|| ((ch>1738) && (ch<1817))   // Received value is an main letter and a join letter of 1707
		  	{
					// DebugPort_sendstring(" Join1707 ");	 
				//NumCount++;
				Temp3+=2;   	                    
	            AVAL1=0;
				CheckFlag2=0;
			

				DispArray[ColCtr++]=0x2000;
				DispArray[ColCtr++]=0x6000;

				Addresstoread = TELUGU_ADD+(LONG)ch*66;

	            do 
				{   
	                val=Read_EEPROM(Addresstoread++);					
					val1=Read_EEPROM(Addresstoread++);	

					firsvalue=(WORD)(val<<8);
					Chr= (WORD)(firsvalue|val1);
                
					CheckWord=Chr;
					CheckByte=(BYTE)(CheckWord>>8);
					CheckByte=(BYTE)CheckByte;
                  
	            /*  	DebugPort_SendStr("CheckByte:  "); 
	                DebugPort_SendByte((CheckByte/10)+0x30);
	                DebugPort_SendByte((CheckByte%10)+0x30);*/
                
	                if(CheckByte==0x00 && CheckFlag2==0)
					{
					      if(AVAL1>=7)
						  {
						 //	GSMPort_sendstring(" check1  "); 
						    Chr1=(Chr|0x6000);
						  	DispArray[ColCtr++]=Chr1;
	                        Chr2=(Chr|0x2000);
	                      	DispArray[ColCtr++]=Chr2; 
	                        CheckFlag2=1;
						  }
						  else
						  {
						    Chr1=(Chr|0xC000);
	                        DispArray[ColCtr++]=Chr1;
						  } 
	                }
					else if((Chr!=0x8888) &&((CheckFlag2==0)))
					{
				      //  GSMPort_sendstring(" check2  "); 
				   	 
						  Chr1=(Chr|0xC000);
	                      DispArray[ColCtr++]=Chr1;
					}
			
					else if(Chr==0x8888 &&((CheckFlag2==0)))
					{
				   //	 GSMPort_sendstring(" check3  "); 
	                   	 DispArray[ColCtr++]=0x6000;
					   	 DispArray[ColCtr++]=0x2000;
					}
					else if(Chr!=0x8888)
						DispArray[ColCtr++]=Chr;
			
	         		AVAL1++;  
	         	}while(Chr!=0x8888);
			 	DispArray[ColCtr++]=0;
                       
			               
			}
			else if((((ch>16) && (ch<472))) && (ch0==1708) )       ///|| ((ch>1738) && (ch<1817)) //Received value is an main letter and a joinb letter of 1708
		  	{       
			//	NumCount++;  
				Temp3+=2; 	                    
				CheckFlag2=0;
				CheckFlag3=0;
				//	DebugPort_sendstring(" Join1708 ");	 
				Chr=0,Chr1=0;
				Addresstoread = TELUGU_ADD+(LONG)ch*66;
				Addresstoread1 = TELUGU_ADD+(LONG)ch0*66;
				do
				{           
				//   GSMPort_sendstring("DISPLAY"); 
					if(CheckFlag2==0 )
					{
						val=Read_EEPROM(Addresstoread++);					
						val1=Read_EEPROM(Addresstoread++);	
						firsvalue=(WORD)(val<<8);
						Chr= (WORD)(firsvalue|val1);
						//	DebugPort_sendstring(" Loop 1 ");
					}
					if(CheckFlag3==0)
					{
						val=Read_EEPROM(Addresstoread1++);					
						val1=Read_EEPROM(Addresstoread1++);	
						firsvalue=(WORD)(val<<8);
						Chr1= (WORD)(firsvalue|val1);
						//	DebugPort_sendstring(" Loop 2 ");
					}


					if((Chr1!=0x8888) && (Chr!=0x8888))
					{ 							  					   
						Chr2=(Chr|Chr1);                                
						DispArray[ColCtr++]=Chr2;
						//DebugPort_sendstring(" Loop 3 ");
					} 
					else if((Chr==0x8888) && (Chr1!=0x8888))
					{  
						CheckFlag2=1;
						//	DebugPort_sendstring(" Loop 4 ");
						DispArray[ColCtr++]=Chr1;
						do 
						{  

						val=Read_EEPROM(Addresstoread1++);					
						val1=Read_EEPROM(Addresstoread1++);	

						firsvalue=(WORD)(val<<8);
						Chr1= (WORD)(firsvalue|val1);
						//CheckFlag3=1;
						if(Chr1==0x8888)
						break;
						DispArray[ColCtr++]=Chr1;

	 		  
						}while(Chr1!=0x8888);

					}
					else if((Chr1==0x8888) && (Chr!=0x8888))
					{     
						CheckFlag3=1;
						DispArray[ColCtr++]=Chr;
						do 
						{ // DebugPort_sendstring(" Loop 5 ");

						val=Read_EEPROM(Addresstoread++);					
						val1=Read_EEPROM(Addresstoread++);	
						firsvalue=(WORD)(val<<8);
						Chr= (WORD)(firsvalue|val1);
						//CheckFlag2=1;
						if(Chr==0x8888)
						break;
						DispArray[ColCtr++]=Chr;

	 		  
						}while(Chr!=0x8888);
					}
					else if((Chr==0x8888) && (Chr1==0x8888))
					break;


				}while((Chr!=0x8888) && (Chr1!=0x8888)); 
				DispArray[ColCtr++]=0;
          
		  	}

		  	else  
		  	{
				Addresstoread =TELUGU_ADD+(LONG)ch*66;
   
				do
				{
					val=Read_EEPROM(Addresstoread++);					
					val1=Read_EEPROM(Addresstoread++);	

					firsvalue=(WORD)(val<<8);
					Chr= (WORD)(firsvalue|val1);

					if(Chr!=0x8888)
					{
						DispArray[ColCtr++]=Chr;
					}


				}while(Chr!=0x8888);

				//	if((ch0!=1738 && ch0!=1736) && (ch0<1709 || ch0>1723 ))							
				if( (ch0!=16) && (ch0<1709 || ch0>1722 ))	//	ch0!=14 &&						
				 DispArray[ColCtr++]=0;
				
		    }
		}
		


	   if(Eng_Flag==0)
		Temp3+=1;
	}
		MyPort_SendByte(0x0d);
		MyPort_SendByte(0x0a);
//	MyPort_SendByte('a');
/*	if(Inter_Flag==1)
	{
		DebugPort_SendStr("Eng");
		while(FontSh[Temp4]!=0xFC)
		{
			ch=FontSh[Temp4++];
			while(pgm_read_word(&Eng_Font[ch-32][index])!=0x8888)
				{
					Chr=pgm_read_word(&Eng_Font[ch-32][index++]);
					DispArray[ColCtr]=Chr;
					//DebugPort_SendByte(DispArray[ColCtr]/256);
					//DebugPort_SendByte(DispArray[ColCtr]%256);
					ColCtr++;	
				}
				DispArray[ColCtr++] = 0;
				DispArray[ColCtr++] = 0;
				DebugPort_SendByte('X');
		}
		if(Temp4<FontLen-1)
		{
			goto form;
		}
	}*/

}	
