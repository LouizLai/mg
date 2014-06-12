/*
 * Input.c
 *
 * Created: 10/06/2014 10:12:24
 *  Author: laicc_000
 */ 

#include <avr/io.h>
#include "Global.h"
enum Button lastkey;

void Input_ReadKBD()
{
	static char oldD;
	char newD=(PIND>>2) & 0x0F;
	char pressed = (newD ^ oldD) & oldD;
	if (pressed & 0x01) lastkey=Left;
	if (pressed & 0x02) lastkey=UpDown;
	if (pressed & 0x04) lastkey=Right;
	if (pressed & 0x08) lastkey=Enter;
	oldD=newD;
}

enum Button Input_GetKey()
{
	enum Button tmp=lastkey;
	lastkey=no;
	return tmp;
}

void Input_Init()
{
	//PORTD=0x7D;	//0111 1101
	//DDRD=0x82;	//1000 0010
}