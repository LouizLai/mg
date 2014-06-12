/*
 * TI.h
 *
 * Created: 01/06/2014 14:15:28
 *  Author: laicc_000
 */ 


#ifndef TI_H_
#define TI_H_

volatile long v_systick;
long systick;
volatile char v_timeStatus;
char timeStatus;

#define F1ms 0x01
#define F10ms 0x02
#define F100ms 0x04
#define F2s 0x08

#define SetF1ms()   v_timeStatus |= F1ms
#define SetF10ms()  v_timeStatus |= F10ms
#define SetF100ms() v_timeStatus |= F100ms
#define SetF2s()    v_timeStatus |= F2s

#define TI_ClrF1ms() timeStatus &= ~F1ms
#define TI_ClrF10ms() timeStatus &= ~F10ms
#define TI_ClrF100ms() timeStatus &= ~F100ms
#define TI_ClrF2s() timeStatus &= ~F2s

#define TI_IsF1ms() (timeStatus & F1ms)
#define TI_IsF10ms() (timeStatus & F10ms)
#define TI_IsF100ms() (timeStatus & F100ms)
#define TI_IsF2s() (timeStatus & F2s)

//functions
void TI_init();
void TI_Update();

#endif /* TI_H_ */

