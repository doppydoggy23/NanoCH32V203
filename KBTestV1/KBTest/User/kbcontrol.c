/*
 * kbcontrol.c
 *
 *  Created on: Feb 25, 2023
 *      Author: COS
 */

#include "stdint.h"
#include "lcd.h"
#include "string.h"
#include <stdio.h>

void kbpresent(void){
    LCDTextXY(0, (8*2)+1, "USB Present", WHITE, 2);
}

void kbhandledata(uint8_t buffer[], int length){

    char tbuf[10];

    // clear screen
    LCD_Fill_Fast(0, (((8*2)+1)*2), LCD_W, LCD_H, BLACK);

    //packet length for a usb keyboard should be from 3 to 8 bytes
    sprintf(tbuf, "Packet Len: %i", length);
    LCDTextXY(0, (((8*2)+1)*2), tbuf, WHITE, 2);

    // print raw data to the screen
    if (length>=3) {
        for (int i=0; i< length; i++){
            sprintf(tbuf, "%X", buffer[i]);
            LCDTextXY((((8*2*2)+1)*i), (((8*2)+1)*3), tbuf, WHITE, 2);
        }
    }

    //for now, we only get and print the first key pressed. Not all characters are recognized, though
    tbuf[0]='!'; //default
    if ((buffer[2]>=4)&&(buffer[2]<=29)) {
        tbuf[0]='A'+(buffer[2]-4);
        tbuf[1]=0;
    }
    if ((buffer[2]>=30)&&(buffer[2]<=38)) {
        tbuf[0]='1'+(buffer[2]-30);
        tbuf[1]=0;
    }
    if (buffer[2]==39) {
        tbuf[0]='0';
        tbuf[1]=0;
    }
    LCDTextXY(100, (((8*2)+1)*7), tbuf, WHITE, 6);
}
