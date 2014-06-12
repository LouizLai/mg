/*
 * logic.c
 *
 * Created: 23/05/2014 08:53:11
 *  Author: laicc_000
 */ 
#include <util/atomic.h>
#include "LCD.h"
#include "global.h"

char original[16] ={box,box,box,box,box,box,box,box,box,box,box,box,box,box,box,box};
char display[16] = {box,box,box,box,box,box,box,box,box,box,box,box,box,box,box,box};
char alpha[16] =   {'a','a','e','e','n','n','q','q','s','s','v','v','x','x','z','z'};
char temp_Col;

char logic_getAlpha(int col)
{
	if(numChar==0) 
	{
		temp_Col=colNow;
	}else{
		if((alpha[temp_Col]==alpha[colNow])&&(temp_Col!=colNow))
		{
			display[temp_Col]=alpha[temp_Col];
			display[colNow]=alpha[colNow];
		}
	}
	return alpha[col];
}

void logic_update()
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
	temp_Col=colNow;
	LCD_gotoXY(0,0);
		for (int i=0; i<16; i++)
		{
			printf("%c", display[i]);
			//printf("%s", "s");
		}
	LCD_gotoXY(temp_Col, 0);
	}
}

int logic_won()
{
	for(short i=0; i<16; i++){
		if(display[i]!=alpha[i]){
			return 0;
		}
	}
	
	return 1;
}

void logic_restart()
{
		for (int i=0; i<16; i++)
		{
			display[i]=box;
		}
}