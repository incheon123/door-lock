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

char scan_Rx(void);
short get_Cx_value(short nums[]);
char checkPassword(const char pw[], const char setted_pw[]);
void set_remain_time_progress(void);
void unset_remain_time_progress(short rt);

#endif /* INC_KEYPAD_H_ */
