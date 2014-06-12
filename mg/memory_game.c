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
	while(1)
	{
		
		TI_Update();
		if(TI_IsF100ms())
		{
			TI_ClrF100ms();
			Input_ReadKBD();
			LCD_Update(Input_GetKey());
		}
		
		if(TI_IsF1s())
		{
			TI_ClrF1s();
			//printf("%i",a);
		}
		
	}
}

void Init()
{
	LCD_Init();
	Input_Init();
	TI_init();
}