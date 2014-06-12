/*
 * l4.c
 *
 * Created: 27/03/2014 15:22:42
 *  Author: laicc_000
 */ 

#include <avr/io.h>
#include "LCD.h"
#include "global.h"

char lastkey;

void input_Init()
{
	PORTD=0xFF; // 1111 1111
	DDRD= 0x82; // 1000 0010
}

void input_enable()
{
	char cmd;
	Input_ReadKBD();
	cmd=Input_GetKey();
		if (cmd)
		{
			switch (cmd)
			{
				case 1: LCD_moveXY(Left);break;
				case 2: LCD_moveXY(Right); break;
				case 3: LCD_moveXY(UpDown);break;
				case 4: LCD_showChar();break;
				default: break;
			}
		}
}

void Input_ReadKBD()
{
	static char oldD;
	char newD=(PIND>>2) & 0x0F;
	char pressed = (newD ^ oldD) & oldD;
	if (pressed & 0x01) lastkey=1;
	if (pressed & 0x02) lastkey=2;
	if (pressed & 0x04) lastkey=3;
	if (pressed & 0x08) lastkey=4;
	oldD=newD;
}

char Input_GetKey()
{
	char tmp=lastkey;
	lastkey=0;
	return tmp;
}
