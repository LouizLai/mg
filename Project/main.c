/*
 * main.c
 *
 * Created: 23.4.2013 22:13:52
 *  Author: mjankovec
 */ 
#include <util/atomic.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "LCD.h"
#include "global.h"

volatile long v_systick;
long systick;
volatile char v_timeStatus;
char timeStatus;

#define F1ms 0x01
#define F10ms 0x02
#define F100ms 0x04
#define F1s 0x08
#define SetF1ms()   v_timeStatus |= F1ms
#define SetF10ms()  v_timeStatus |= F10ms
#define SetF100ms() v_timeStatus |= F100ms
#define SetF1s()    v_timeStatus |= F1s
#define ClrF1ms() timeStatus &= ~F1ms
#define ClrF10ms() timeStatus &= ~F10ms
#define ClrF100ms() timeStatus &= ~F100ms
#define ClrF1s() timeStatus &= ~F1s
#define IsF1ms() (timeStatus & F1ms)
#define IsF10ms() (timeStatus & F10ms)
#define IsF100ms() (timeStatus & F100ms)
#define IsF1s() (timeStatus & F1s)

int main()
{
	LCD_Init();
	input_Init();
	main_Init();
	//LCD_writeString("Hello World?");
	
	//fprintf( &LCDstr, "%d, %x, %s", 10, 10, "");
	stdout = &LCDstr;
	//LCD_gotoXY(1, 1);
	//printf("%d, %x, %s", 11, 12, "str");
	//for (int i = 0; i<32; i++){
	//	printf("%c", 219);
	//}
	logic_update();
	while(1)
	{
		UpdateVolatileVariables();
		input_enable();
		if(IsF10ms())
		{
			ClrF10ms();

		}
		if(IsF1ms())
		{
			ClrF1ms();

		}
		if(IsF100ms()){
			ClrF100ms();
		}
		if(IsF1s()){
			ClrF100ms();
			logic_update();
		}
		if(logic_won())
		{
			LCD_gotoXY(0,0);
			printf("%s","You won!Press any key to restart");
			_delay_ms(2000);
			logic_restart();
			logic_update();
		}
	}
}

void main_Init()
{
	//external interrupt 0
	EICRA=(1<<ISC01);
	EIMSK=(1<<INT0);
	
	//timer 0  - set for 1ms
	TCCR0A=2;
	TCCR0B=4;
	OCR0A=71;
	TIMSK0=(1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
	static int cnt10, cnt100, cnt1000;
	v_systick++;
	SetF1ms();
	if (cnt10 >= 10)
	{
		cnt10 = 0;
		SetF10ms();
	}
	cnt10++;
	if (cnt100 >= 100)
	{
		cnt100 = 0;
		SetF100ms();
	}
	cnt100++;
	if (cnt1000 >= 1000)
	{
		cnt1000 = 0;
		SetF1s();
	}
	cnt1000++;
}

void UpdateVolatileVariables()
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		systick = v_systick;
		timeStatus |= v_timeStatus;
		v_timeStatus=0;
	}
	
}
