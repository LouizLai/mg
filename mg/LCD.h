/*
 * LCD.h
 *
 * Created: 23.4.2013 22:14:06
 *  Author: mjankovec
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>			//knjiznica z definicijami registrov
#define F_CPU 18432000UL	// dolocitev frekvence oscilatorja za funkcije iz delay.h - mora biti pred #include <util/delay.h>
#include <util/delay.h>		//knjiznica s funkcijami delay
#include <stdio.h>
#include "Global.h"
//Definicije prikljucitve LCD - spreminja uporabnik

#define LCD_DataPort	PORTA
#define LCD_DataPin		PINA
#define LCD_DataDir		DDRA
#define LCD_DataMask	0xf0 //1111 0000
#define LCD_Shift		4	 //0000 DDDD -> DDDD 0000

#define LCD_E_Port	PORTC
#define LCD_E_Dir	DDRC
#define LCD_E_Mask	0x01

#define LCD_RW_Port	PORTC
#define LCD_RW_Dir	DDRC
#define LCD_RW_Mask	0x40

#define LCD_RS_Port	PORTC
#define LCD_RS_Dir	DDRC
#define LCD_RS_Mask	0x80

#define LCD_Backlight_Port	PORTD
#define LCD_Backlight_Dir	DDRD
#define LCD_Backlight_Mask	0x80


// definicije kontrolnih signalov

#define LCD_E_set()	LCD_E_Port |= LCD_E_Mask
#define LCD_E_clr()	LCD_E_Port &= ~LCD_E_Mask

#define LCD_R()	LCD_RW_Port |= LCD_RW_Mask; LCD_DataDir &= ~LCD_DataMask
#define LCD_W()	LCD_RW_Port &= ~LCD_RW_Mask; LCD_DataDir |= LCD_DataMask

#define LCD_DR()	LCD_RS_Port |= LCD_RS_Mask
#define LCD_IR()	LCD_RS_Port &= ~LCD_RS_Mask

#define LCD_Backlight_ON()	LCD_Backlight_Port |= LCD_Backlight_Mask;	//prizgi osvetlitev
#define LCD_Backlight_OFF()	LCD_Backlight_Port &= ~LCD_Backlight_Mask;	//prizgi osvetlitev

// definicije pisanja na podatkovno vodilo // 0000 xxxx    // dddd xxxx
#define LCD_Write_Nibble(x)	LCD_DataPort &= ~LCD_DataMask; LCD_DataPort |= (x<<LCD_Shift)

//definicija enum podatkovnega tipa LCD_register
enum LCD_Register {Data=0,Instr=1};

extern FILE LCDstr;
//enum Button {no=0, Left=5, Right=2, UpDown=3, Enter=4};
char LCD_Busy();
void LCD_BusyWait(unsigned int timeout);
void LCD_Write(enum LCD_Register reg, char data);
void LCD_Init();
void LCD_gotoXY(char col, char line);
void LCD_writeString(char *txt);
int LCD_putch(char c, FILE *stream);

void LCD_Update(enum Button dir);
void LCD_ShowChar();
#endif /* LCD_H_ */