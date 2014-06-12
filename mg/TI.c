/*
 * TI.c
 * 
 * TI: Timer interrupt
 * Created: 01/06/2014 13:53:32
 *  Author: laicc_000
 */ 

#include <util/atomic.h>
#include <avr/interrupt.h>


#include "Global.h"
#include "TI.h"

void TI_Update()
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		systick = v_systick;
		timeStatus |= v_timeStatus;
		v_timeStatus=0;
	}
}

ISR(TIMER0_COMPA_vect)
{
	static int cnt10, cnt100, cnt2000;
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
	if (cnt2000 >= 2000)
	{
		cnt2000 = 0;
		SetF2s();
	}
	cnt2000++;
}

void TI_init()
{
	//external interrupt 0
	EICRA=(1<<ISC01);
	EIMSK=(1<<INT0);
	//timer 0  - set for 1ms
	TCCR0A=2;
	TCCR0B=4;
	OCR0A=71;
	TIMSK0=(1<<OCIE0A);
	
	//enable global interrupt
	sei();
}


