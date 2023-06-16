#ifndef __LCD_H__
#define __LCD_H__

#define LCD_W 240
#define LCD_H 240

#define WHITE            0xFFFF
#define BLACK            0x0000
#define BLUE             0x001F
#define BRED             0XF81F
#define GRED                   0XFFE0
#define GBLUE                  0X07FF
#define RED              0xF800
#define MAGENTA          0xF81F
#define GREEN            0x07E0
#define CYAN             0x7FFF
#define YELLOW           0xFFE0
#define BROWN                0XBC40 //×ØÉ«
#define BRRED                0XFC07 //×ØºìÉ«
#define GRAY                 0X8430 //»ÒÉ«
#define DARKBLUE         0X01CF //ÉîÀ¶É«
#define LIGHTBLUE        0X7D7C //Ç³À¶É«
#define GRAYBLUE         0X5458 //»ÒÀ¶É«
#define LIGHTGREEN       0X841F //Ç³ÂÌÉ«
#define LGRAY                0XC618 //Ç³»ÒÉ«(PANNEL),´°Ìå±³¾°É«
#define LGRAYBLUE        0XA651 //Ç³»ÒÀ¶É«(ÖÐ¼ä²ãÑÕÉ«)
#define LBBLUE           0X2B12 //Ç³×ØÀ¶É«(Ñ¡ÔñÌõÄ¿µÄ·´É«)

typedef uint16_t u16;

int lcd_init();

void LCD_Fill_Fast(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);

//fontSize must be a multiple of 2
void LCDTextXY(int textX, int textY, char *myString, int color, int fontSize);

void LCDPutPixel(int X, int Y, int color);
void LCDDrawLine(int x0, int y0, int x1, int y1, int color);

#endif /* __LCD_H__ */
