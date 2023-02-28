/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/*
 *@Note
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.

*/

#include "debug.h"
#include "lcd.h"

/* Global typedef */

/* Global define */

/* Global Variable */

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    RCC_ClocksTypeDef RCC_ClocksStatus={0};


/*OLD    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);

    printf("This is printf example\r\n");*/



    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    Delay_Ms(100);
    USART_Printf_Init(115200);
    printf("SystemClk:%ld\r\n", SystemCoreClock);

    SystemCoreClockUpdate();
    printf("SystemClk:%d\r\n",SystemCoreClock);

    RCC_GetClocksFreq(&RCC_ClocksStatus);
    printf("SYSCLK_Frequency-%d\r\n", RCC_ClocksStatus.SYSCLK_Frequency);
    printf("HCLK_Frequency-%d\r\n", RCC_ClocksStatus.HCLK_Frequency);
    printf("PCLK1_Frequency-%d\r\n", RCC_ClocksStatus.PCLK1_Frequency);
    printf("PCLK2_Frequency-%d\r\n", RCC_ClocksStatus.PCLK2_Frequency);

    /* NOT NEEDED printf("GPIO Toggle TEST\r\n");
    GPIO_Toggle_init();*/

    lcd_init();

    //int colors[5]={RED, GREEN, BLUE, WHITE, BLACK};
    //int k=0;

    LCD_Fill_Fast(0,0,240,240,BLACK); // clear screen black

    char* text="Hello World!";
    int textPosX=12;
    int textPosY=53;
    const int textWidth=((12*8)*2);
    const int textHeight=((1*8)*2);
    int textDirX=1;
    int textDirY=1;

    while(1)
    {
        //clear current ball position
        LCD_Fill_Fast(textPosX,textPosY,textPosX+textWidth,textPosY+textHeight,BLACK);

        //check for bounds
        if (textPosX+textWidth>=240){
            textDirX=-1;
        }
        if (textPosY+textHeight>=240){
            textDirY=-1;
        }
        if (textPosX<=0){
            textDirX=+1;
        }
        if (textPosY<=0){
            textDirY=+1;
        }

        //update ball pos
        textPosX+=textDirX;
        textPosY+=textDirY;

        //draw ball in the new position
        LCDTextXY(textPosX,textPosY,text,WHITE, 2); // fontsize must be a muntiple of 2

        //
        Delay_Ms(5);
    }
}
