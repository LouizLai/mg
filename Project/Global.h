/*
 * global.h
 *
 * Created: 23/05/2014 10:10:40
 *  Author: laicc_000
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

enum charCode {box=219};
static char colNow = 0, rowNow = 0;
int abs(int a);

//main
void main_Init();
void UpdateVolatileVariables();

//input
void input_Init();
void input_enable();
void Input_ReadKBD();
char Input_GetKey();


void input_ReadKBD();
char Input_GetKey();
//logic
char logic_getAlpha(int col);
void logic_update();
int logic_won();
void logic_restart();
#endif /* GLOBAL_H_ */