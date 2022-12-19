/******************************
 * switch.c
 * 
 * 4x4 Switch
 * 
 * 			 COL1  COL2  COL3  COL4
 * 		ROW1  S1    S2    S3    S4
 * 		ROW2  S5    S6    S7    S8
 * 		ROW3  S9    S10   S11   S12
 * 		ROW4  S13   S14   S15   S16
 ******************************/

#include "switch.h"


//////////////////////////////////////////////////
// Variable

int ROW[4] = {ROW1, ROW2, ROW3, ROW4};
int COL[4] = {COL1, COL2, COL3, COL4};
int sw_pushed[16] = {0, };
int idx_pushed[16] = {0, };


//////////////////////////////////////////////////
// Function Definition

void SW_Init(void)
{
	// 4x4 Switch Init
	pinMode(ROW1, OUTPUT);
	pinMode(ROW2, OUTPUT);
	pinMode(ROW3, OUTPUT);
	pinMode(ROW4, OUTPUT);
	pinMode(COL1, INPUT);
	pinMode(COL2, INPUT);
	pinMode(COL3, INPUT);
	pinMode(COL4, INPUT);

	pullUpDnControl(COL1, PUD_UP);			
	pullUpDnControl(COL2, PUD_UP);			
	pullUpDnControl(COL3, PUD_UP);			
	pullUpDnControl(COL4, PUD_UP);			
}


void ROW_select(int num) {
	int i;
	
	for (i = 0; i < 4; i++) {
		digitalWrite(ROW[i], (i==num ? 0 : 1));
	}

}


int* SW_Check(void) {
	int i, j;
	
	for (i = 0; i < 16; i++) {					// sw_pushed Reset
		sw_pushed[i] = 0;
	}

	printf("\n--- Check ---\n");

	for (i = 0; i < 4; i++) {					// 4 ROWs
		ROW_select(i);							// Select ROW[i]
		
		for (j = 0; j < 4; j++) {				// 4 COLs
			if (digitalRead(COL[j]) == LOW) {	// Check Switch Clicked
				sw_pushed[4*i + j] = 1;
			}
		}
	}

	printf("\n");
	for (i = 0; i < 16; i++)
		printf("%d ", sw_pushed[i]);
	printf("\n\n");
	
	return sw_pushed;
}


// find index which value 1
int* Index_Check(int* array) {
	int i, j=0;
	
	for(i = 0; i < 16; i++) {
		idx_pushed[i] = 0;			// Clear array
		if(array[i] == 1) {
			idx_pushed[j++] = i;	// Put Index
		}
	}
	idx_pushed[j] = -1;		// Finish
	
	return idx_pushed;
}

