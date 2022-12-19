/****************************************
 * Term Project
 * 
 ********************
 * Author: Nam Sujin - 2019146011 (Embedded System)
 * 
 * Date: 2022-12-19
 * 
 ********************
 * < Reflexes Game >
 * 		GAME MODE
 * 			GAME1 - Click Number
 * 			GAME2 - Click Area
 * 		
 * 		H/W
 * 			Raspberry Pi 4B
 * 			4x4 Switch
 * 			8x8 Dot Matrix (MAX7219)
 * 			LCD
 * 		
 * 		Interface
 * 			GPIO
 * 			SPI - Dot Matrix
 * 			I2C - LCD
 * 		
 * 		S/W
 * 			language: C
 * 			main
 * 				L Switch
 * 				L Dot Matrix
 * 				L LCD
 * 
 ********************
 * make
 * 		gcc -c -o main.o main.c
 * 		gcc -c -o switch.o switch.c
 * 		gcc -c -o dotmatrix.o dotmatrix.c
 * 		gcc -c -o lcd.o lcd.c
 * 		gcc -o final main.o switch.o dotmatrix.o lcd.o -lwiringPi -lbcm2835
 * 
 * execute
 * 		sudo ./final
 * 
 ****************************************/


#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "main.h"


//////////////////////////////////////////////////
// Variable

int STATE = HOME;
float game_result = 0;
struct timeb milli_now;
struct tm *now;

// LCD Output array
char arrs_menu_1[2][16] = {
	"< Click Number >", 
	"<  Match Area  >", 
//	"<  Multi Click >", 
//	"<  Random Mode >", 
};


//////////////////////////////////////////////////
// main


int main(int argc, char** argv)
{
	int* sw_clicked;
	int* idx_clicked;
	int i;
	int index = 0;
	
	// Init
	if (!bcm2835_init()) {
		printf("Unable to init bcm2835.\n");
		return 2;
	}
	
	Port_Init();
	
	ClrLcd();			// LCD Clear
	dot_num_print(17);	// Dot Matrix Clear
	
	
	// Process
	while (1) {
		process(STATE);
	}
	
	return 0;
}



//////////////////////////////////////////////////
// Function Definition

void Port_Init(void) {
	// GPIO Setting (wiringPi)
	wiringPiSetup();
	
	// Switch
	SW_Init();
	
	// Dot Matrix
	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);		// The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);						// The default
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);		// The default
	bcm2835_gpio_fsel(Max7219_pinCS, BCM2835_GPIO_FSEL_OUTP);
	Delay_xms(50);
	Init_MAX7219();
	
	// LCD
	LCD_Init();
}


void select_GAME(int menu){
	switch (menu) {
		case 0:
			STATE = GAME1;
			break;
		case 1:
			STATE = GAME2;
			break;
		case 2:
			STATE = GAME3;
			break;
		case 3:
			STATE = GAME4;
			break;
		default:
			STATE = HOME;
			break;
	}
}


int random_num(int start, int end){
	int num;
	
	srand((unsigned int)time(NULL));
	
	num = (int)((rand() % (end - start + 1)) + start);
	
	return num;
}


float present_time() {
	float pre_time;
	
	ftime(&milli_now);
	now = localtime(&milli_now.time);
	
	pre_time = now->tm_sec + (milli_now.millitm/1000.0);
	
	return pre_time;
}


void process(int state){
	switch (state) {
		case HOME:		func_HOME();
						break;
						
		case MENU:		func_MENU();
						break;
						
		case GAME1:		game_result = func_GAME1();
						break;
						
		case GAME2:		game_result = func_GAME1();
						break;
						
		case GAME3:		func_HOME();
						break;
						
		case GAME4:		func_HOME();
						break;
						
		case RESULT:	func_RESULT(game_result);
						break;
						
		default:		func_HOME();
						break;
	}
}


//==================== STATE Function ====================
//
void func_HOME(void){
	int* sw_clicked;
	int* idx_clicked;
	
	printf("\n--- HOME ---\n");
	
	ClrLcd();
    lcdLoc(LINE1);
    typeln(" REFLEXES  GAME ");
    lcdLoc(LINE2);
    typeln("...press any key");
    delay(1000);
    
    while(1) {
		sw_clicked = SW_Check();
		idx_clicked = Index_Check(sw_clicked);
		
		if (idx_clicked[0] != -1) {
			STATE = MENU;
			return;
		}
	}
}


void func_MENU(void){
	int* sw_clicked;
	int* idx_clicked;
	int menu = 0;
	
	printf("\n--- MENU ---\n");
	printf("menu = %d\n", menu);
	
	ClrLcd();
	lcdLoc(LINE2);
	typeln("[S1]Next  [S2]OK");
	lcdLoc(LINE1);
	typeln(arrs_menu_1[menu]);
	
	while(1) {
		sw_clicked = SW_Check();
		idx_clicked = Index_Check(sw_clicked);
		
		if (idx_clicked[0]+1 == 1) {			// [S1] Next
			if (++menu >= MAX_GAME) {
				menu = 0;
			}
			lcdLoc(LINE1);
			typeln(arrs_menu_1[menu]);
			delay(500);
		}
		else if (idx_clicked[0]+1 == 2) {		// [S2] OK
			select_GAME(menu);
			return;
		}
	}
	
	select_GAME(menu);
	return;
}


float func_GAME1(void){
	int cnt;
	int stage = 0;
	int goal = 0;
	int number = 0;
	int* sw_clicked;
	int* idx_clicked;
	float start_time;
	float each_time;
	float total_time = 0.0;
	char array[20];
	
	printf("\n--- GAME1 ---\n");
	
	
	// ----- READY ----- //
	ClrLcd();
	lcdLoc(LINE1);
	typeln("Click Number!");
	
	for (cnt = 3; cnt >= 0; cnt--) {
		lcdLoc(LINE2);
		sprintf(array, "READY: %d  ", cnt);
		typeln(array);
		delay(1000);
	}
	
	
	// ----- GAME START ----- //
	for (stage = 1; stage <= 10; stage++) {
		number = 0;
		goal = random_num(1, 16);
		printf("goal: %d\n", goal);
		
		// LCD
		ClrLcd();
		lcdLoc(LINE1);
		sprintf(array, "STAGE %2d        ", stage);
		typeln(array);
		
		// Dot Matrix
		if (STATE == GAME1) {
			dot_num_print(goal);
		}
		else if (STATE == GAME2) {
			dot_area_print(goal);
		}
		
		start_time = present_time();
		
		while (number == 0) {
			sw_clicked = SW_Check();
			idx_clicked = Index_Check(sw_clicked);
			number = idx_clicked[0] + 1;
			
			each_time = present_time() - start_time;
			
			// Limit 3 seconds
			if (each_time > 3) {
				number = -1;
				each_time = 3;
			}
			
		}
		
		if (goal == number) {
			// LCD
			lcdLoc(LINE1);
			typeln("  !!! HIT !!!   ");
		}
		else {
			each_time += 3.0;	// Wrong -> 3 seconds Extra Penalty
			// LCD
			lcdLoc(LINE1);
			typeln(" --- Missed --- ");
		}
		
		lcdLoc(LINE2);
		sprintf(array, "       +%8.4fs", each_time);
		typeln(array);
		
		total_time += each_time;
		
		// Clear DotMatrix
		dot_num_print(17);
		
		delay(1000);	// wait for next stage
	}
	
	
	// ----- GAME FINISH ----- //
	STATE = RESULT;
	return total_time;
}


void func_RESULT(float result){
	int* sw_clicked;
	int* idx_clicked;
	char array[20];
	
	printf("\n--- RESULT ---\n");
	
	ClrLcd();
    lcdLoc(LINE1);
    sprintf(array, "RESULT %7.4fs", result);
    typeln(array);
    lcdLoc(LINE2);
    typeln("...press any key");
    delay(1000);
    
	while(1) {
		sw_clicked = SW_Check();
		idx_clicked = Index_Check(sw_clicked);
		
		if (idx_clicked[0] != -1) {
			STATE = HOME;
			return;
		}
	}
}

