/*
 * mousecontrol.c
 *
 *  Created on: Feb 27, 2023
 *      Author: COS
 */

#ifndef USER_MOUSECONTROL_C_
#define USER_MOUSECONTROL_C_


#include "stdint.h"
#include "lcd.h"
#include "string.h"
#include <stdio.h>
#include "mousecontrol.h"

int mouse_button_L=0;
int mouse_button_R=0;

void mousepresent(void){
    //LCDTextXY(0, (8*2)+1, "USB Present", WHITE, 2);
}

void mousehandledata(uint8_t buffer[], int length){

    /*
     * Handling a usb mouse is tricky. Some send 3 bytes with 1 bytes per direction and others
     * send 5 bytes, two bytes per direction. Others even have a completely different protocol.
     * We used https://wiki.osdev.org/USB_Human_Interface_Devices and only read the buttons
     */
    if (length>=3) {
        if (buffer[0]&1) {
            mouse_button_L=1;
        }
        else {
            mouse_button_L=0;
        }

        if (buffer[0]&2) {
            mouse_button_R=1;
        }
        else {
            mouse_button_R=0;
        }
    }

}

void getMouseButtons(int *L, int *R)
{
    *L=mouse_button_L;
    *R=mouse_button_R;
    /*mouse_button_L=0;
    mouse_button_R=0;*/
}

#endif /* USER_MOUSECONTROL_C_ */
