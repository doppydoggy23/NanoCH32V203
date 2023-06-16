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
#include <stdio.h>
#include <stdlib.h>
//#include "formulas.h"

#define M_PI (3.1415927f)
#define M_PI_2 (M_PI/2.0f)
#define M_PI_M_2 (M_PI*2.0f)

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

void TIM3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
extern void TIM3_Init( uint16_t arr, uint16_t psc );
void toggleLED();

//initializes timer 3
void TIM3_Init( uint16_t arr, uint16_t psc )
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure = { 0 };
    NVIC_InitTypeDef NVIC_InitStructure = { 0 };

    /* Enable timer3 clock */
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );

    /* Initialize timer3 */
    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );

    /* Enable updating timer3 interrupt */
    TIM_ITConfig( TIM3, TIM_IT_Update, ENABLE );

    /* Configure timer3 interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init( &NVIC_InitStructure );

    /* Enable timer3 */
    TIM_Cmd( TIM3, ENABLE );

    /* Enable timer3 interrupt */
    NVIC_EnableIRQ( TIM3_IRQn );
}

int myCount=0; //increments every 1ms

// this function will be executed every 1ms
void TIM3_IRQHandler( void )
{
    if( TIM_GetITStatus( TIM3, TIM_IT_Update ) != RESET )
    {
        /* Clear interrupt flag */
        TIM_ClearITPendingBit( TIM3, TIM_IT_Update );

        if (myCount>500) { // if count>500ms, blink led
            myCount=0;
            toggleLED();
        }
        myCount++;
    }
}

// sets IO pins
void GPIO_Toggle_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

u8 i = 0;

//toggle LED IO pin
void toggleLED() {
    GPIO_WriteBit(GPIOA, GPIO_Pin_15, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
}

//3d functions prototypes
float myround(float p);

void projectCube(float cube[8][3], float cubeProjected[8][2], float F, int xcenter, int ycenter);
void drawCube(float cubeProjected[8][2], int color);
void scaleCube(float cubep[8][3], float cubeTR[8][3], float xs, float ys, float zs);


void moveCube(float cubep[8][3], float cubeTR[8][3], float xs, float ys, float zs);


void rotateCubeInX(float cubep[8][3], float cubeRotp[8][3], float XAngle);

void rotateCubeInY(float cubep[8][3], float cubeRotp[8][3],float YAngle);
void rotateCubeInZ(float cubep[8][3], float cubeRotp[8][3],float ZAngle);

void rotateCube(float cube[8][3], float cubeRot[8][3], float XAngle, float YAngle, float ZAngle);

int compare_float(double f1, double f2);
double cos(double x);
double sin(double x);
//
///
//

int main(void)
{

    Delay_Init();

    lcd_init();

    GPIO_Toggle_init();

    TIM3_Init( 9, SystemCoreClock / 10000 - 1 ); // timer will counts MSs
    // since real frequency will be = SystemCoreClock/ (10000/(9+1))


    LCD_Fill_Fast(0,0,240,240,BLACK); // clear screen black
    char* text="Hello World!";
    LCDTextXY(0,0,text,WHITE, 2); // fontsize must be a muntiple of 2
    //
    char text2[20];
    sprintf (text2, "%i hz", SystemCoreClock); // should output 96Mhz
    LCDTextXY(0,(8*2)+1,text2,WHITE, 2); // fontsize must be a muntiple of 2

/* FIRST TEST FAILED
 * char text2[100];
    float myf=1.21;
    sprintf(text2, "%f", myf);
    LCDTextXY(0,(8*2)+1,text2,WHITE, 2);
    //

    /* TEST 2 PASSED
    char text2[10];
    float myf=1.21;
    float myf2=1.5;
    int mysum=round(myf+myf2);
    sprintf(text2, "%i", mysum);
    LCDTextXY(0,(8*2)+1,text2,WHITE, 2);
    */

    /*LCDPutPixel (100, 100, RED);
    LCDDrawLine(110, 110, 200, 200, WHITE);
    LCDDrawLine(88, 68, 150, 170, WHITE);
    LCDDrawLine(68, 58, 270, 70, WHITE);
    */

    float cube[8][3]= {
        //upper
        {-1, 1, 1}, //front
        {1, 1, 1}, //front
        {-1, 1, -1}, //back
        {1, 1, -1}, //back
        //lower
        {-1, -1, 1},//front
        {1, -1, 1},//front
        {-1, -1, -1},//back
        {1, -1, -1}// back
    };
    float cubeProjected[8][2], cubeScaled[8][3], cubeMoved[8][3], cubeRotated[8][3];


    rotateCube(cube, cubeRotated, 0.5, 0.5, 0.5);
    scaleCube(cubeRotated, cubeScaled, 20, 20, 20);
    moveCube(cubeScaled, cubeMoved, 0, 0, 75);
    projectCube(cubeMoved, cubeProjected, 100, 120, 120);
    drawCube(cubeProjected, WHITE);


    float xAngle=0, yAngle=0, zAngle=0;
    while(1)
    {
        //LCD_Fill_Fast(0,0,240,240,BLACK); // clear screen black
        //Delay_Ms(500);
        //LCD_Fill_Fast(0,0,240,240,RED); // clear screen black
        //Delay_Ms(1000);
        //toggleLED();

        /*int x0=rand()/240;
        int y0=rand()/240;
        int x1=rand()/240;
        int y1=rand()/240;
        LCDDrawLine(x0, y0, x1, y1, WHITE);
        */

        /*Delay_Ms(1000);
        LCDDrawLine(0, 0, 240, 240, RED);
        Delay_Ms(1000);
        LCDDrawLine(240, 0, 0, 240, BLUE);
        */

        /*int x0=((float)rand()/(float)RAND_MAX)*240;
        int y0=((float)rand()/(float)RAND_MAX)*240;
        int x1=((float)rand()/(float)RAND_MAX)*240;
        int y1=((float)rand()/(float)RAND_MAX)*240;
        LCDDrawLine(x0, y0, x1, y1, WHITE);
        */

        drawCube(cubeProjected, BLACK);// clear cube from screen

        if (xAngle>2*M_PI)
            xAngle=0;
        if (yAngle>2*M_PI)
            yAngle=0;
        if (zAngle>2*M_PI)
            zAngle=0;

        xAngle+=M_PI/50;
        yAngle+=M_PI/50;
        zAngle+=M_PI/50;

        rotateCube(cube, cubeRotated, xAngle, yAngle, zAngle);
        scaleCube(cubeRotated, cubeScaled, 20, 20, 20);
        moveCube(cubeScaled, cubeMoved, 0, 0, 75);
        projectCube(cubeMoved, cubeProjected, 100, 120, 120);
        drawCube(cubeProjected, WHITE);

        Delay_Ms(5);
    }
}


//
// 3D functions
//

float myround(float p){ // some weird mounriver studio bug doesn't let us use math.h round()
    return (int)(p);
}

void projectCube(float cube[8][3], float cubeProjected[8][2], float F, int xcenter, int ycenter) {
    for (int i=0; i<8; i++) {
        //xc = x / z
        //yc = y / z
        //cubeProjected[i][0]=cube[i][0]/cube[i][2];
        //cubeProjected[i][1]=cube[i][1]/cube[i][2];
        /////cubeProjected[i][0]=myround(cube[i][0]*(F/cube[i][2]));
        /////cubeProjected[i][1]=myround(cube[i][1]*(F/cube[i][2]));
        cubeProjected[i][0]=myround(cube[i][0]*F/cube[i][2]);
        cubeProjected[i][1]=myround(cube[i][1]*F/cube[i][2]);

        // center at 200, 200
        cubeProjected[i][0]+=xcenter;
        cubeProjected[i][1]+=ycenter;
    }
}

void drawCube(float cubeProjected[8][2], int color)
{
    LCDDrawLine (cubeProjected[0][0], cubeProjected[0][1], cubeProjected[1][0], cubeProjected[1][1], color);
    LCDDrawLine (cubeProjected[2][0], cubeProjected[2][1], cubeProjected[3][0], cubeProjected[3][1], color);
    LCDDrawLine (cubeProjected[0][0], cubeProjected[0][1], cubeProjected[2][0], cubeProjected[2][1], color);
    LCDDrawLine (cubeProjected[1][0], cubeProjected[1][1], cubeProjected[3][0], cubeProjected[3][1], color);

    LCDDrawLine (cubeProjected[0+4][0], cubeProjected[0+4][1], cubeProjected[1+4][0], cubeProjected[1+4][1], color);
    LCDDrawLine (cubeProjected[2+4][0], cubeProjected[2+4][1], cubeProjected[3+4][0], cubeProjected[3+4][1], color);
    LCDDrawLine (cubeProjected[0+4][0], cubeProjected[0+4][1], cubeProjected[2+4][0], cubeProjected[2+4][1], color);
    LCDDrawLine (cubeProjected[1+4][0], cubeProjected[1+4][1], cubeProjected[3+4][0], cubeProjected[3+4][1], color);

    LCDDrawLine (cubeProjected[0][0], cubeProjected[0][1], cubeProjected[4][0], cubeProjected[4][1], color);
    LCDDrawLine (cubeProjected[1][0], cubeProjected[1][1], cubeProjected[5][0], cubeProjected[5][1], color);
    LCDDrawLine (cubeProjected[2][0], cubeProjected[2][1], cubeProjected[6][0], cubeProjected[6][1], color);
    LCDDrawLine (cubeProjected[3][0], cubeProjected[3][1], cubeProjected[7][0], cubeProjected[7][1], color);
}

void scaleCube(float cubep[8][3], float cubeTR[8][3], float xs, float ys, float zs){
    for (int i=0; i<8; i++) {
        cubeTR[i][0]=cubep[i][0]*xs;
        cubeTR[i][1]=cubep[i][1]*ys;
        cubeTR[i][2]=cubep[i][2]*zs;
    }
}


void moveCube(float cubep[8][3], float cubeTR[8][3], float xs, float ys, float zs){
    for (int i=0; i<8; i++) {
        cubeTR[i][0]=cubep[i][0]+xs;
        cubeTR[i][1]=cubep[i][1]+ys;
        cubeTR[i][2]=cubep[i][2]+zs;
    }
}


void rotateCubeInX(float cubep[8][3], float cubeRotp[8][3], float XAngle) {
    for (int i=0; i<8; i++) {
        // X Axis Rotation
        //    Xnew = Xold
        //    Ynew = Yold x cos¦È ¨C Zold x sin¦È
        //    Znew = Yold x sin¦È + Zold x cos¦È
        cubeRotp[i][0]=cubep[i][0];
        cubeRotp[i][1]=(cubep[i][1]*cos(XAngle))-(cubep[i][2]*sin(XAngle));
        cubeRotp[i][2]=(cubep[i][1]*sin(XAngle))+(cubep[i][2]*cos(XAngle));
    }
}

void rotateCubeInY(float cubep[8][3], float cubeRotp[8][3],float YAngle) {
    for (int i=0; i<8; i++) {
        //Y Axis Rotation
        //Xnew = Zold x sin¦È + Xold x cos¦È
        //Ynew = Yold
        //Znew = Yold x cos¦È ¨C Xold x sin¦È
        cubeRotp[i][0]=(cubep[i][2]*sin(YAngle))+(cubep[i][0]*cos(YAngle));
        cubeRotp[i][1]=cubep[i][1];
        cubeRotp[i][2]=(cubep[i][1]*cos(YAngle))-(cubep[i][0]*sin(YAngle));
    }
}

void rotateCubeInZ(float cubep[8][3], float cubeRotp[8][3],float ZAngle) {
    for (int i=0; i<8; i++) {
        //Z Axis Rotation
        //Xnew = Xold x cos¦È ¨C Yold x sin¦È
        //Ynew = Xold x sin¦È + Yold x cos¦È
        //Znew = Zold
        cubeRotp[i][0]=(cubep[i][0]*cos(ZAngle))-(cubep[i][1]*sin(ZAngle));
        cubeRotp[i][1]=(cubep[i][0]*sin(ZAngle))+(cubep[i][1]*cos(ZAngle));
        cubeRotp[i][2]=cubep[i][2];
    }
}


void rotateCube(float cube[8][3], float cubeRot[8][3], float XAngle, float YAngle, float ZAngle) {
    float cubeTemp[8][3], cubeTemp2[8][3];

    rotateCubeInX(cube, cubeTemp, XAngle);
    rotateCubeInY(cubeTemp, cubeTemp2, YAngle);
    rotateCubeInZ(cubeTemp2, cubeRot, ZAngle);
}


int compare_float(double f1, double f2)
{
 double precision = 0.00000000000000000001;
 if ((f1 - precision) < f2)
  {
 return -1;
  }
 else if ((f1 + precision) > f2)
 {
  return 1;
 }
 else
  {
 return 0;
  }
}

// we have to have our own sin/cos functions because mounRiver studio doesn't let us use the ones in math.h
double cos(double x){
 if( x < 0.0f )
  x = -x;

  if (0 <= compare_float(x,M_PI_M_2))
 {
 do {
  x -= M_PI_M_2;
  }while(0 <= compare_float(x,M_PI_M_2));

  }

  if ((0 <= compare_float(x, M_PI)) && (-1 == compare_float(x, M_PI_M_2)))
  {
   x -= M_PI;
   return ((-1)*(1.0f - (x*x/2.0f)*( 1.0f - (x*x/12.0f) * ( 1.0f - (x*x/30.0f) * (1.0f - (x*x/56.0f )*(1.0f - (x*x/90.0f)*(1.0f - (x*x/132.0f)*(1.0f - (x*x/182.0f)))))))));
  }
 return 1.0f - (x*x/2.0f)*( 1.0f - (x*x/12.0f) * ( 1.0f - (x*x/30.0f) * (1.0f - (x*x/56.0f )*(1.0f - (x*x/90.0f)*(1.0f - (x*x/132.0f)*(1.0f - (x*x/182.0f)))))));
}

double sin(double x){return cos(x-M_PI_2);}
