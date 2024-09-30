/*
 * keypad.c
 *
 *  Created on: Sep 17, 2024
 *      Author: kth
 */
#include <stdio.h>
#include <string.h>
#include "keypad.h"

char scan_Rx(void)
{
	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);

	if(!(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin)));
		return '1';
	}
	if(!(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin)));
		return '2';
	}
	if(!(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)));
		return '3';
	}
	if(!(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin)));
		return 'A';
	}
	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);
	if(!(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin)));
		return '4';
	}
	if(!(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin)));
		return '5';
	}
	if(!(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)));
		return '6';
	}
	if(!(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin)));
		return 'B';
	}
	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);
	if(!(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin)));
		return '7';
	}
	if(!(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin)));
		return '8';
	}
	if(!(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)));
		return '9';
	}
	if(!(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin)));
		return 'C';
	}
	HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);
	if(!(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin)));
		return '0';
	}
	if(!(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin)));
		return '-';
	}
	if(!(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)));
		return '#';
	}
	if(!(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin)))
	{
		while(!(HAL_GPIO_ReadPin(C4_GPIO_Port, C4_Pin)));
		return '*';
	}

	return 255;
}

/*
 * pw 		 : pw that user press
 * setted_pw : door-lock password
 */
char checkPassword(const char *pw, const char *setted_pw)
{
	printf("checkPassword called\n");
	if(!strcmp(pw, setted_pw))
	{
		printf("Access Success\n");//오늘 처음 알았는데 문자열 마지막에 \n 추가 안해주면  Tera Term에서 인식 못함....
	}else
	{
		printf("Access Denied\n");
	}
}

void set_remain_time_progress(void)
{
	for(int i = 0; i < remain_time; i++)
	{
	  HD44780_SetCursor(i, 1);
	  HD44780_PrintSpecialChar(0xFF);
	}
}

void unset_remain_time_progress(short rt)
{
  HD44780_SetCursor(rt, 1);
  HD44780_PrintSpecialChar(0x20);
}
