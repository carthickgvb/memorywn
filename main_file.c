/************************************************
							Memory Game Project
									main file
************************************************/

#include <at89c5131.h>
#include "lcd.h"
#include "varsfuns.c"

void main(void){
	unsigned int i;
	
	lcd_init();
	uart_init();
	
	while(1){
		score=0;
		initial_state=state;																		
		
		//Display 10 word-digit pairs
		for(i=0;i<10;i++){																																
			DisplayWord(state,0x85);
			DisplayNum(state,0x8A);
			msdelay(1000);
			state = NextState(state);
			lcd_cmd(0x01);
		}
		
		DisplayString("Get Ready",0x84);
		msdelay(3000);
		lcd_cmd(0x01);
		
		//Display only word and any digit typed within 3s
		for(i=0;i<10;i++){														
			ES=1;
			DisplayWord(initial_state,0x85);
			msdelay(3000);
			initial_state = NextState(initial_state);
			lcd_cmd(0x01);
		}
		
		//Display current score and high score
		if(score>maxscore){maxscore=score;}											
		DisplayString("Score:",0x80);	
		DisplayNum(48+(score/10),0x8E);
		DisplayNum(48+(score%10),0x8F);
		DisplayString("High Score:",0xC0);
		DisplayNum(48+(maxscore/10),0xCE);
		DisplayNum(48+(maxscore%10),0xCF);
		msdelay(3000);
		lcd_cmd(0x01);		
	}
}