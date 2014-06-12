/*
 * global.h
 *
 * Created: 23/05/2014 10:10:40
 *  Author: laicc_000
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

//enums
enum Button {no=9, Left=0, Right=1, UpDown=2, Enter=3};
enum charCode {box=219};

char colNow, rowNow;
char numChar;


int abs(int a);

//main
void Init();
void TI_Update();

//input
void Input_ReadKBD();
enum Button Input_GetKey();
void Input_Init();


//logic
char logic_getAlpha(int col);
void logic_update();
int logic_won();
void logic_restart();


//LCD
void LCD_Update(enum Button dir);



#endif /* GLOBAL_H_ */