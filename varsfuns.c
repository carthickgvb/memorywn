/************************************************

	Variables and functions are defined here
	
************************************************/


#include <at89c5131.h>

//Variables
unsigned int state=1;
unsigned int initial_state=1;
unsigned int score=0,maxscore=0;
unsigned char *words = "kingidealeftgoodexittaxichef1avacafelogovisafujiechojavaasiapoemcubademoduetladypumpnextnewsyearbookmasknicesnownullunittime";


//Function definitions
/************************************************
	Prints string on LCD at 
	the given position
************************************************/

void DisplayString(unsigned char *x,unsigned int pos){
	lcd_cmd(pos);
	lcd_write_string(x);
}


/************************************************
	Prints a specific word on LCD
	among "words" at the given
	position
************************************************/
void DisplayWord(unsigned x, unsigned int pos){
	lcd_cmd(pos);
	lcd_write_char(*(words+4*x-4));
	lcd_write_char(*(words+4*x-3));
	lcd_write_char(*(words+4*x-2));
	lcd_write_char(*(words+4*x-1));
}


/************************************************
	Prints Number on LCD at
	the given postion
************************************************/
void DisplayNum(unsigned x, unsigned int pos){
	lcd_cmd(pos);
	lcd_write_char(48+((x%16)%10));
}


/************************************************
	Returns the next LFSR state
************************************************/
unsigned int NextState(unsigned int x){
	return (x/2)+16*(((x%16)/8)^(x%2));
}


/************************************************
	Increments score if typed num 
	is correct
************************************************/
void AdjustScore(void){
	if(SBUF==(48+((initial_state%16)%10))){
		score++;
	}
}


/**********************************************************
	Initializes UART peripheral for 8-bit transfer, 
	1 start and 1 stop bits. 
	
	TH1 value for 1200 baud rate
***********************************************************/	
void uart_init(void)
{
	TMOD=0x20;  //Configure Timer 1 in Mode 2
	TH1=204;    //Load TH1 to obtain require Baudrate (Refer Serial.pdf for calculations)
	SCON=0x50;  //Configure UART peripheral for 8-bit data transfer 
	TR1=1;	    //Start Timer 1
	EA=1;	    //Enable Serial Interrupt
	ES=0;	    //Enable Global Interrupt
}


/************************************************
	serial interrupt service routine
	prints the typed character and 
	implements adjust score
************************************************/
void serial_ISR(void) interrupt 4
{
		if(RI==1) //check whether RI is set
		{
			RI = 0;	//Clear RI flag
			DisplayNum(SBUF-48,0xC7);
			AdjustScore();
			ES=0;
		}
		else if(TI==1) //check whether TI is set
		{
			TI = 0;	//Clear TI flag
		}
}

/************************************************
	end of function definitions
************************************************/
