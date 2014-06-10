/*
 * LCD.c
 *
 * Created: 23.4.2013 13:07:37
 *  Author: mjankovec
 */ 
#include "Global.h"
#include "LCD.h"

FILE LCDstr = FDEV_SETUP_STREAM(LCD_putch, NULL, _FDEV_SETUP_WRITE);

int LCD_putch(char c, FILE *stream)
{
	//recognize \n, \r
	//for \n
		if(c == '\n'){
			LCD_gotoXY(0, ~rowNow);
			return 0;
		}
		
		if(c == '\r'){
			LCD_gotoXY(0, rowNow);
			return 0 ;
		}
		
	
	LCD_Write(Data, c);
	//change line
	colNow++;
	if(colNow>15&&rowNow==0){
		LCD_gotoXY(0,~rowNow);
	}
	//display word by word
	_delay_ms(100);
	return 0;
}

//************************************
// Method:    LCD_Busy
// FullName:  LCD_Busy
// Access:    public 
// Returns:   char
// Qualifier: Funkcija vrne 0, ?e je LCD pripravljen za vpis podatka
//************************************

char LCD_Busy()
{
	char data;

	//D4 - D7 = PORTA 4-7
	//RS(PC7) = 0, RW(PC6) = 1, E(PC0)
	LCD_IR();
	LCD_R();
	
	//Tu beremo zgornje 4 bite
	LCD_E_set();
	asm("nop");
	asm("nop");
	data = LCD_DataPin; //preberi zgornje stiri bite
	LCD_E_clr();
	asm("nop");
	asm("nop");
	
	//Tu beremo spodnje 4 bite (samo da jih v bistvu ignoriramo)
	LCD_E_set();
	asm("nop");
	asm("nop");
	LCD_E_clr();
	
	if (data & 0x80)	return 1;	// if busy flag is 1, its busy
	else return 0;	// LCD is ready to do your bidding
}



//************************************
// Method:    LCD_BusyWait
// FullName:  LCD_BusyWait
// Access:    public 
// Returns:   void
// Qualifier: funkcija ?aka, dokler ni LCD pripravljen ali dokler ne pote?e timeout. Timeout je odvisen od ure procesorja.
// Parameter: unsigned int timeout
//************************************
void LCD_BusyWait(unsigned int timeout)
{
	for (unsigned int i=0;i<timeout;i++)
	{
		if (!LCD_Busy()) break;
	}	
}

//************************************
// Method:    LCD_Write
// FullName:  LCD_Write
// Access:    public 
// Returns:   void
// Qualifier: Funkcija vpiše podatek v LCD
// Parameter: enum LCD_Register reg
// Parameter: char data
//************************************
void LCD_Write(enum LCD_Register reg, char data)
{
	char temp;
	
	LCD_BusyWait(1000);
	
	//D4 - D7 = PORTA 4-7

	if (reg == Instr) LCD_IR(); // piši v inštrukcijski register
	else LCD_DR(); // piši v podatkovni register
	
	LCD_W();
	LCD_E_set();
	
	// write high nibble
	temp = data>>4;	 // dddd 0000 -> 0000 dddd
	LCD_Write_Nibble(temp);

	LCD_E_clr();
	asm("nop");
	asm("nop");
	
	LCD_E_set();
	
	// write low nibble
	temp = data & 0x0F;	 //  0000 dddd
	LCD_Write_Nibble(temp);
	
	LCD_E_clr();
}

//************************************
// Method:    LCD_Init
// FullName:  LCD_Init
// Access:    public 
// Returns:   void
// Qualifier: Funkcija inicializira LCD
//************************************
void LCD_Init()
{
	//nastavi ustrezne pine kot izhode
	LCD_E_Dir |= LCD_E_Mask;
	LCD_RS_Dir |= LCD_RS_Mask;
	LCD_RW_Dir |= LCD_RW_Mask;
	LCD_DataDir |= LCD_DataMask;
	LCD_Backlight_Dir |= LCD_Backlight_Mask;
	
	LCD_Backlight_ON();
	_delay_ms(15);
	LCD_IR();
	LCD_W();
	LCD_E_set();
	LCD_Write_Nibble(3);
	LCD_E_clr();
	_delay_ms(5);
	LCD_E_set();
	LCD_Write_Nibble(3);
	LCD_E_clr();
	_delay_ms(100);
	LCD_E_set();
	LCD_Write_Nibble(3);
	LCD_E_clr();
	
	LCD_BusyWait(1000);
	LCD_E_set();
	LCD_Write_Nibble(2);
	LCD_E_clr();
	
	LCD_Write(Instr,0x28); //4-bit interface (bit4)
	LCD_Write(Instr,0x08);
	LCD_Write(Instr,0x01);
	LCD_Write(Instr,0x06); //B1=1(Left to Right?) B0=0(no display shift)
	
	LCD_Write(Instr,0x0F); //Display, cursor, blink, all on. 
}

void LCD_gotoXY(char col, char line){
	
	char cmd;
	//cmd=0x80 |line*0x40 col;
	cmd=0x80 | (line & 0x01)<<6 | (col&0x0F);
	LCD_Write(Instr,cmd);
	colNow = col;
	rowNow = line;
}

void LCD_writeString(char *txt){
	
	for (int i=0; txt[i]; i++){
		LCD_Write(Data, txt[i]);
	colNow++;
	if(colNow>15&&rowNow==0){
		LCD_gotoXY(0,~rowNow);
	}
	}
}

void LCD_moveXY(enum LCD_DirXY dir){
	switch (dir)
	{
		case Left: LCD_gotoXY(abs((--colNow)%16), rowNow);break;
		case Right: LCD_gotoXY(abs((++colNow)%16), rowNow); break;
		case UpDown: LCD_gotoXY(colNow, rowNow==0?1:0); break;
		default: break;
	}}