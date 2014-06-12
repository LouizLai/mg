/*
 * logic.c
 *
 * Created: 23/05/2014 08:53:11
 *  Author: laicc_000
 */ 
#include "LCD.h"
#include "global.h"
char display[2][16] = {{box,box,box,box,box,box,box,box,box,box,box,box,box,box,box,box},{box,box,box,box,box,box,box,box,box,box,box,box,box,box,box,box}};
char original[2][16] ={{box,box,box,box,box,box,box,box,box,box,box,box,box,box,box,box},{box,box,box,box,box,box,box,box,box,box,box,box,box,box,box,box}};
char alpha[2][16] =   {{'a','c','e','m','n','p','q','r','s','u','v','w','x','y','z','g'},{'a','c','e','m','n','p','q','r','s','u','v','w','x','y','z','g'}};

int tempRow;
int tempCol;
int first=1;

char logic_getAlpha(int col, int row)
{
	if(first){
		tempRow = row;
		tempCol = col;
		first=0;
	}else{
		if((alpha[tempRow][tempCol]==alpha[row][col])&&!((tempRow==row)&&(tempCol==col))){
			//display[tempRow][tempCol]=alpha[tempRow][tempCol];
			//display[row][col]=alpha[row][col];
		}
		first=1;
	}
	
	return alpha[row][col];
}

void logic_update()
{
	LCD_gotoXY(0,0);
	for (int j=0; j<2;j++)
	{
		for (int i=0; i<16; i++)
		{
			printf("%c", display[j][i]);
		}
	}
	LCD_gotoXY(colNow, rowNow);

	
}

int logic_won()
{
	return display==alpha?1:0;
}

void logic_restart()
{
	for (int j=0; j<2;j++)
	{
		for (int i=0; i<16; i++)
		{
			display[j][i]=box;
		}
	}
}