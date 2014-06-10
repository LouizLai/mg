/*
 * memory_game.c
 *
 * Created: 01/06/2014 14:52:16
 *  Author: laicc_000
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "TI.h"
#include "LCD.h"
#include "Global.h"

char a = 1;

int main(void)
{
	Init();
	stdout=&LCDstr;
	while(1)
	{
		TI_Update();
		printf("%i",TI_IsF10ms());
		if(TI_IsF10ms())
		{
			TI_ClrF10ms();
			PORTB = a;
		}
		
	}
}



void Init()
{
	TI_init();
	LCD_Init();
}