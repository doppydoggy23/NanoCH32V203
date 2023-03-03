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

//our asm function
extern void updateBall(int *ballXPos, int *ballYPos, int ballWidth, int ballHeight, int *ballXDispp, int *ballYDispp);

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

    lcd_init();

    int ballX=20;
    int ballY=15;
    int ballWidth=10;
    int ballHeight=8;
    int ballXDisp=1;
    int ballYDisp=1;


    while(1)
    {
        // clean ball
        LCD_Fill_Fast(ballX, ballY, ballX+ballWidth, ballY+ballHeight, BLACK);

        // call our asm function
        updateBall(&ballX, &ballY, ballWidth, ballHeight, &ballXDisp, &ballYDisp);

        //draw ball
        LCD_Fill_Fast(ballX, ballY, ballX+ballWidth, ballY+ballHeight, WHITE);
        Delay_Ms(5);
    }
}
