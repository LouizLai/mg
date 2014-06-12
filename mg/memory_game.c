/*
 * memory_game.c
 *
 * Created: 01/06/2014 14:52:16
 *  Author: laicc_000
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "LCD.h"
#include "Global.h"
#include "TI.h"

char a = 1;


int main(void)
{
	Init();
	stdout=&LCDstr;
	for(int i=0; i<16;i++)
	{
		printf("%c",box);
	}
	LCD_gotoXY(0,0);
	while(1)
	{
		TI_Update();
		if(TI_IsF100ms())
		{
			TI_ClrF100ms();
			Input_ReadKBD();
			LCD_Update(Input_GetKey());
		}
		
		if(TI_IsF2s())
		{
			TI_ClrF2s();
			//printf("%i",a);
			if(numChar>=2)
			{
				logic_update();
				numChar=0;
			}
			
		}
		if(logic_won())
		{
			printf("%s","you won!");
		}
	}
}

void Init()
{
	LCD_Init();
	Input_Init();
	TI_init();
}