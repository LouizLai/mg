/*
 * global.h
 *
 * Created: 23/05/2014 10:10:40
 *  Author: laicc_000
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_

char colNow, rowNow;

int abs(int a);

//functions

//main
void Init();

//input
void input_Init();
void input_enable();
void input_ReadKBD();
char Input_GetKey();

/*
//logic
char logic_getAlpha(int col, int row);
void logic_update();
int logic_won();
void logic_restart();
*/


//enums
enum LCD_DirXY {Left=0, Right=1, UpDown=2};
enum charCode {box=219};

#endif /* GLOBAL_H_ */