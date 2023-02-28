/*
 * mousecontrol.h
 *
 *  Created on: Feb 27, 2023
 *      Author: COS
 */

#ifndef USER_MOUSECONTROL_H_
#define USER_MOUSECONTROL_H_



void mousepresent(void);
void mousehandledata(uint8_t buffer[], int length);
void getMouseButtons(int *L, int *R);

#endif /* USER_MOUSECONTROL_H_ */
