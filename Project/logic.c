/*
 * logic.c
 *
 * Created: 23/05/2014 08:53:11
 *  Author: laicc_000
 */ 
#include <util/atomic.h>
#include "LCD.h"
#include "global.h"
char display[16] = {box,box,box,box,box,box,box,box,box,box,box,box,box,box,box,box};
char original[16] ={box,box,box,box,box,box,box,box,box,box,box,box,box,box,box,box};
char alpha[16] =   {'a','c','e','m','n','p','q','r','s','u','v','w','x','y','z','g'};

int tempRow;
int tempCol;
char temp_Col;
int first=1;

char logic_getAlpha(int col)
{
	if(first){
		tempCol = col;
		first=0;
	}else{
		if((alpha[tempCol]==alpha[col])&&!(tempCol==col)){
			//display[tempRow][tempCol]=alpha[tempRow][tempCol];
			//display[row][col]=alpha[row][col];
		}
		first=1;
	}
	
	return alpha[col];
}

void logic_update()
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
	temp_Col=colNow;
	LCD_gotoXY(0,1);
		for (int i=0; i<15; i++)
		{
			//printf("%c", display[i]);
			//printf("%s", "s");
		}
	LCD_gotoXY(temp_Col, 1);
	}
}

int logic_won()
{
	return display==alpha?1:0;
}

void logic_restart()
{
		for (int i=0; i<16; i++)
		{
			display[i]=box;
		}
}