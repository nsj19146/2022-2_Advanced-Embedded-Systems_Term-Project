/*
 * dotmatrix.h
 */

#ifndef __DOTMATRIX_H__
#define __DOTMATRIX_H__


//////////////////////////////////////////////////
// Include

#include <bcm2835.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


//////////////////////////////////////////////////
// Define

//#define Max7219_pinDIN  RPI_GPIO_P1_19		// 10 (wPi)
#define Max7219_pinCS  RPI_GPIO_P1_24		//  8 (wPi)
//#define Max7219_pinCLK  RPI_GPIO_P1_23		// 11 (wPi)


//////////////////////////////////////////////////
// Function

void Delay_xms(unsigned int x);
void Write_Max7219_byte(unsigned char data);
void Write_Max7219(unsigned char address, unsigned char data);
void Init_MAX7219();
void dot_num_print(int num);
void dot_area_print(int area);

//////////////////////////////////////////////////

#endif

