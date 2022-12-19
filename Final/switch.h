/*
 * switch.h
 */

#ifndef __SWITCH_H__
#define __SWITCH_H__


//////////////////////////////////////////////////
// Include

#include <wiringPi.h>
#include <stdio.h>


//////////////////////////////////////////////////
// Define

// 4x4 Switch ROW, COL
#define ROW1	25	// GPIO 26	(PIN 37)
#define ROW2	24	// GPIO 19	(PIN 35)
#define ROW3	23	// GPIO 13	(PIN 33)
#define ROW4	22	// GPIO  6	(PIN 31)
#define COL1	29	// GPIO 21	(PIN 40)
#define COL2	28	// GPIO 20	(PIN 38)
#define COL3	27	// GPIO 16	(PIN 36)
#define COL4	26	// GPIO 12	(PIN 32)


//////////////////////////////////////////////////
// Function

void SW_Init(void);
void ROW_select(int);
int* SW_Check(void);
int* Index_Check(int*);

//////////////////////////////////////////////////

#endif
