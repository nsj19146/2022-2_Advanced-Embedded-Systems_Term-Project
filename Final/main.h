/*
 * main.h
 */

#ifndef __MAIN_H__
#define __MAIN_H__

//////////////////////////////////////////////////
// include

#include <wiringPi.h>
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>
#include "switch.h"
#include "dotmatrix.h"
#include "lcd.h"


//////////////////////////////////////////////////
// define

// STATE
#define HOME		0
#define MENU		1
#define GAME1		2
#define GAME2		3
#define GAME3		4
#define GAME4		5
#define RESULT		9

#define MAX_GAME	2

//////////////////////////////////////////////////
// function

void Port_Init(void);
void select_GAME(int menu);
int random_num(int start, int end);
float present_time();

void process(int state);

// for STATE  (HOME, MENU, GAME1, GAME2, RESULT)
void func_HOME(void);
void func_MENU(void);
float func_GAME1(void);
void func_RESULT(float result);


//////////////////////////////////////////////////

#endif
