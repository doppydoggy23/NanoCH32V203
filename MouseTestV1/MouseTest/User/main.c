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
#include "mousecontrol.h"
#include "USB_Host/usb_host_config.h"
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

    /* Initialize TIM3 */
    TIM3_Init( 9, SystemCoreClock / 10000 - 1 );
    DUG_PRINTF( "TIM3 Init OK!\r\n" );

    /* Initialize USBFS host */
#if DEF_USBFS_PORT_EN
    DUG_PRINTF( "USBFS Host Init\r\n" );
    USBFS_RCC_Init( );
    USBFS_Host_Init( ENABLE );
    memset( &RootHubDev.bStatus, 0, sizeof( ROOT_HUB_DEVICE ) );
    memset( &HostCtl[ DEF_USBFS_PORT_INDEX * DEF_ONE_USB_SUP_DEV_TOTAL ].InterfaceNum, 0, sizeof( HOST_CTL ) );
#endif

    /* NOT NEEDED printf("GPIO Toggle TEST\r\n");
    GPIO_Toggle_init();*/

    lcd_init();

    //int colors[5]={RED, GREEN, BLUE, WHITE, BLACK};
    //int k=0;

    LCD_Fill_Fast(0,0,240,240,BLACK); // clear screen black


    //LCDTextXY(0, 0, "Hello World", WHITE, 2);

    int barPosX=100;
    int barPosY=220;
    int barWidth=50;
    int barHeight=20;
    int mouseBR, mouseBL;
    int ballX=10;
    int ballY=0;
    int ballWidth=20;
    int ballHeight=18;
    int ballDispX=1;
    int ballDispY=1;

    while(1)
    {
        // delay for a few MS doing nothing but update the USB
        for (int i=0; i<5; i++) {
        USBH_MainDeal();
        Delay_Ms(1);
        }

        // clean the screen
        LCD_Fill_Fast(barPosX, barPosY, barPosX+barWidth, barPosY+barHeight, BLACK);
        LCD_Fill_Fast(ballX, ballY, ballX+ballWidth, ballY+ballHeight, BLACK);


        // get mouse buttons and act accordingly
        getMouseButtons(&mouseBL, &mouseBR);
        if (mouseBL){
            barPosX-=1;
        }
        if (mouseBR){
            barPosX+=1;
        }

        // test for bar out of bounds
        if ((barPosX+barWidth)>=LCD_W) {
            barPosX=LCD_W-barWidth;
        }
        if ((barPosX)<=0) {
            barPosX=0;
        }

        // check for ball bounds
        if ((ballY+ballHeight)>=LCD_H) {
            // we lose
            barPosX=100;
            barPosY=220;
            ballX=10;
            ballY=0;
            ballDispX=1;
            ballDispY=1;
        }
        if (ballY<=0) {
            ballDispY=+1;
        }
        //
        if (ballX<=0) {
            ballX=0;
            ballDispX=1;
        }
        if ((ballX+ballWidth)>=LCD_W) {
            ballX=LCD_W-ballWidth;
            ballDispX=-1;
        }
        if ((ballY+ballHeight)>=barPosY) {
            if (((ballX+ballWidth)>=barPosX)&&((ballX+ballWidth)<=(barPosX+barWidth))){
                ballDispY=-1;
            }
            if ((ballX>=barPosX)&&(ballX<=(barPosX+barWidth))){
                ballDispY=-1;
            }
        }

        // update ball
        ballX+=ballDispX;
        ballY+=ballDispY;

        // draw the bar and ball
        LCD_Fill_Fast(barPosX, barPosY, barPosX+barWidth, barPosY+barHeight, WHITE);
        LCD_Fill_Fast(ballX, ballY, ballX+ballWidth, ballY+ballHeight, WHITE);
    }
}
