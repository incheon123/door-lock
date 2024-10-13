/*
 * keypad.c
 *
 *  Created on: Sep 17, 2024
 *      Author: kth
 */
#include <stdio.h>
#include <string.h>
#include "keypad.h"

short success_set_remain_time_progress = 0;

static Pos pos;

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
		while(!(HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin))); // prevent from long press.
		return '-';
	}
	if(!(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)))
	{
//		while(!(HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)));
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
	if(!strcmp(pw, setted_pw))
	{
		printf("Good\n");
		finish_system("Door Unlocked");
	}else
	{
		printf("Failed!!\n");
	}
}

void set_remain_time_progress(void)
{
	for(int i = 0; i < remain_time; i++)
	{
	  HD44780_SetCursor(i, 1);
	  HD44780_PrintSpecialChar(0xFF);
	}
	success_set_remain_time_progress = 1;
}

void unset_remain_time_progress(short rt)
{
  HD44780_SetCursor(rt, 1);
  HD44780_PrintSpecialChar(0x20);
}

void clear_character(short col, short row)
{
	HD44780_SetCursor(col, row);
	HD44780_PrintSpecialChar(0x20);
}
void set_cursor_pos(short col, short row)
{
	pos.col = col;
	pos.row = row;
	HD44780_SetCursor(col, row);
	printf("col : %d row : %d\n", pos.col, pos.row);
}
Pos get_cursor_pos()
{
	return pos;
}

short check_change_pw_key_pressed(short* long_press_cnt, short* gp_timer)
{
	while( !HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin) &&
		   !HAL_GPIO_ReadPin(R4_GPIO_Port, R4_Pin) )
	{
		if(*long_press_cnt == 0)	// 0s
		{
			*long_press_cnt = *gp_timer;
		}else if(*gp_timer >= *long_press_cnt + 2000)	// 2s
		{

			return 1;
		}
	}

	*long_press_cnt = 0;
	return 0;
}
short changePassword(char original_password[], short size)
{
	HD44780_Clear();
	HD44780_PrintStr("Change Password");

	char key;
	short pw_idx = 0;
	char pw[10] = "\0";
	while(1)
	{
		while((key = scan_Rx()) == 255) ;

		if( key == '#')
		{
			continue;
		}else if(key != 255 && pw_idx <= 5)
		{
			HD44780_Clear();
			pw[pw_idx++] = key;
			HD44780_PrintStr(pw);
		}else if(key == '-')
		{
			for(int i = 0 ; i < 6; i++)
				original_password[i] = pw[i];
			original_password[6] = '\0';
			return 1;
		}
	}

	return 0;
}
void home(char* str)
{
	HD44780_Init(2);
	HD44780_PrintStr(str);
}
void finish_system(char* msg)
{
	HD44780_Clear();
	HD44780_PrintStr(msg);
	HAL_Delay(2000);
	HD44780_Clear();
	HD44780_Home();
	HD44780_NoBacklight();
	HD44780_NoDisplay();
}
