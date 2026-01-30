//For telugu display  places

#define SIZE               12
#define TOLERENCE          1
#define ROUTE_MAX          12

/*
const BYTE Eloc[SIZE][11] PROGMEM =
{
 //VIJAYAWADA TO CHENNAI CENTRAL

{0,1,2,3,4,63,1,60,100},                 //VIJAYAWADA
{5,6,7,63,1,60,100},                     //TENALI
{8,9,10,11,63,1,60,100},                 //NIDUBROLU
{12,13,14,100},
{15,16,17,100},                 		 //CHIRALA
{18,19,20,11,100},              		 //ONGOLE
{21,19,22,16,2,23,19,4,100},     		 //SINGARAYAKONDA
{24,25,7,100},                  		 //KAVALI
{26,27,28,100},                  		 //NELLORE
{29,30,28,63,1,60,100},                  //GUDUR
{31,27,28,32,33,100},           		 //SULLURUPETA
{34,35,36,19,37,38,100},       			 //CHENNAI CENTRAL

};


//VIJAYAWADA TO VISHAKAPATNAM

//{0,1,2,3,4,63,1,60,100},                 //VIJAYAWADA
//{39,40,28,100},                  //ELURU
//{41,42,13,43,44,4,60,100},         //TADEPALLIGUDEM
//{8,4,61,46,11,63,1,60,100},               //NIDADAVOLU
//{16,1,48,19,47,100},          //RAJAMUNDRY
//{49,48,43,23,33,63,1,60,100},             //SAMALKOT
//{50,51,25,52,60,100},               //ANNAVARAM
//{57,8,100},                      //THUNI
//{50,53,24,13,43,100},            //ANAKAPALLE
//{9,62,4,100},                  //DUVVADA
//{0,54,55,13,56,19,100},          //VISHAKAPATNAM

*/


//TELUGU
//=====

const BYTE Eloc[SIZE][10] PROGMEM =
{
{0,1,2,3,4,63,1,60,100},                 //VIJAYAWADA JN

{48,81,52,100},                            //MADHIRA

{85,86,19,100},  		          //KHAMMAM

{48,82,83,12,12,47,100},            /MAHABOOBA  BAD

{25,16,19,22,38,100},                      //WARANGAL

{84,95,93,94,63,1,60,100},                    //KHAZIPET JN

{92,53,89,90,91,100},                   //BHUVANAGIRI

{-,88,87,12,41,63,1,60,100},                           //SECUNDERABAD  JN 88 or 23 

};  

