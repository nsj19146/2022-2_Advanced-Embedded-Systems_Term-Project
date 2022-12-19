/*
 * lcd.h
 */

#ifndef __LCD_H__
#define __LCD_H__


//////////////////////////////////////////////////
// Include

#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>


//////////////////////////////////////////////////
// Define

#define I2C_ADDR   0x27 // I2C device address

#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line

#define LCD_BACKLIGHT   0x08  // On (LCD_BACKLIGHT = 0x00  # Off)

#define ENABLE  0b00000100 // Enable bit


//////////////////////////////////////////////////
// Function

void ClrLcd(void);				// Clear LCD return home
void lcdLoc(int line);			// move cursor
void typeChar(char val);
void typeln(const char *s);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);
void LCD_Init(void);

//////////////////////////////////////////////////

#endif
