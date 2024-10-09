/*
 * keypad.h
 *
 *  Created on: 2024. 9. 18.
 *      Author: kth
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_


#include "main.h"

#define remain_time 10

typedef struct
{
	short col;
	short row;
}Pos;

char scan_Rx(void);
short get_Cx_value(short nums[]);
char checkPassword(const char pw[], const char setted_pw[]);
void set_remain_time_progress(void);
void unset_remain_time_progress(short rt);
void clear_character(short col, short row);
void set_cursor_pos(short col, short row);
Pos get_cursor_pos();

short check_change_pw_key_pressed(short* long_press_cnt, short* gp_timer);
short changePassword(char original_password[], short size);
#endif /* INC_KEYPAD_H_ */
