/******************************************************************************
* | File      	:   gui_traffic_lights.c
* | Author      :   Luke Mulder
* | Function    :	Draw a traffic intersection with 4 traffic lights
* | Info        :
*
*----------------
* |	This version:   V1.0
* | Date        :   2024-06-05
* | Info        :
* -----------------------------------------------------------------------------
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documnetation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to  whom the Software is
* furished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
******************************************************************************/
#define LOG_LEVEL_ERROR

#include "gui_traffic_lights.h"
#include "hal_lcd.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h> //memset()
#include <math.h>

uint16_t frame_buf[1][1] = {0};

/******************************************************************************
  function: Draw Pixels
  parameter:
    Xpoint  :   At point X
    Ypoint  :   At point Y
    color   :   Painted colors
******************************************************************************/
void GUI_SetPixel(uint16_t Xpoint, uint16_t Ypoint, uint16_t color)
{
  Hal_LCD_DrawPoint(Xpoint, Ypoint, color);
}

/******************************************************************************
  function: Clear the color of the picture
  parameter:
    color   :   Painted colors
******************************************************************************/
void GUI_Clear(uint16_t color)
{
  Hal_LCD_ClearWindow(0, 0, LCD_HEIGHT, LCD_WIDTH, color);
}

/******************************************************************************
function:	Draw Point(Xpoint, Ypoint) Fill the color
parameter:
    Xpoint		:   The Xpoint coordinate of the point
    Ypoint		:   The Ypoint coordinate of the point
    color		:   Set color
    Dot_Pixel	:	point size
******************************************************************************/
void GUI_DrawPoint( uint16_t Xpoint,       uint16_t Ypoint, uint16_t color,
                      DOT_PIXEL Dot_Pixel,DOT_STYLE Dot_FillWay)
{
    int16_t XDir_Num , YDir_Num;
    if (Dot_FillWay == DOT_FILL_AROUND) {
        for (XDir_Num = 0; XDir_Num < 2*Dot_Pixel - 1; XDir_Num++) {
            for (YDir_Num = 0; YDir_Num < 2 * Dot_Pixel - 1; YDir_Num++) {
                if(Xpoint + XDir_Num < Dot_Pixel || Ypoint + YDir_Num < Dot_Pixel)
                    break;
                // printf("x = %d, y = %d\r\n", Xpoint + XDir_Num - Dot_Pixel, Ypoint + YDir_Num - Dot_Pixel);
                GUI_SetPixel(Xpoint + XDir_Num - Dot_Pixel, Ypoint + YDir_Num - Dot_Pixel, color);
            }
        }
    } else {
        for (XDir_Num = 0; XDir_Num <  Dot_Pixel; XDir_Num++) {
            for (YDir_Num = 0; YDir_Num <  Dot_Pixel; YDir_Num++) {
                GUI_SetPixel(Xpoint + XDir_Num - 1, Ypoint + YDir_Num - 1, color);
            }
        }
    }
}

/******************************************************************************
function:	Draw a line of arbitrary slope
parameter:
    Xstart ：Starting Xpoint point coordinates
    Ystart ：Starting Xpoint point coordinates
    Xend   ：End point Xpoint coordinate
    Yend   ：End point Ypoint coordinate
    color  ：The color of the line segment
******************************************************************************/
void GUI_DrawLine(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, 
                    uint16_t color, DOT_PIXEL Line_width, LINE_STYLE Line_Style)
{
    uint16_t Xpoint = Xstart;
    uint16_t Ypoint = Ystart;
    int dx = (int)Xend - (int)Xstart >= 0 ? Xend - Xstart : Xstart - Xend;
    int dy = (int)Yend - (int)Ystart <= 0 ? Yend - Ystart : Ystart - Yend;

    // Increment direction, 1 is positive, -1 is counter;
    int XAddway = Xstart < Xend ? 1 : -1;
    int YAddway = Ystart < Yend ? 1 : -1;

    //Cumulative error
    int Esp = dx + dy;
    char Dotted_Len = 0;

    for (;;) {
        Dotted_Len++;
        //Painted dotted line, 2 point is really virtual
        if (Line_Style == LINE_STYLE_DOTTED && Dotted_Len % 3 == 0) {
            //LOG_ERROR("LINE_DOTTED\r\n");
            GUI_DrawPoint(Xpoint, Ypoint, IMAGE_BACKGROUND, Line_width, DOT_STYLE_DFT);
            Dotted_Len = 0;
        } else {
            GUI_DrawPoint(Xpoint, Ypoint, color, Line_width, DOT_STYLE_DFT);
        }
        if (2 * Esp >= dy) {
            if (Xpoint == Xend)
                break;
            Esp += dy;
            Xpoint += XAddway;
        }
        if (2 * Esp <= dx) {
            if (Ypoint == Yend)
                break;
            Esp += dx;
            Ypoint += YAddway;
        }
    }
}

/******************************************************************************
function:	Draw a rectangle
parameter:
    Xstart ：Rectangular  Starting Xpoint point coordinates
    Ystart ：Rectangular  Starting Xpoint point coordinates
    Xend   ：Rectangular  End point Xpoint coordinate
    Yend   ：Rectangular  End point Ypoint coordinate
    color  ：The color of the Rectangular segment
    Filled : Whether it is filled--- 1 solid 0：empty
******************************************************************************/
void GUI_DrawRectangle(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, 
                          uint16_t color, DOT_PIXEL Line_width, DRAW_FILL Filled )
{
    if (Filled ) {
        uint16_t Ypoint;
        for(Ypoint = Ystart; Ypoint < Yend; Ypoint++) {
            GUI_DrawLine(Xstart, Ypoint, Xend, Ypoint, color ,Line_width, LINE_STYLE_SOLID);
        }
    } else {
        GUI_DrawLine(Xstart, Ystart, Xend, Ystart, color ,Line_width, LINE_STYLE_SOLID);
        GUI_DrawLine(Xstart, Ystart, Xstart, Yend, color ,Line_width, LINE_STYLE_SOLID);
        GUI_DrawLine(Xend, Yend, Xend, Ystart, color ,Line_width, LINE_STYLE_SOLID);
        GUI_DrawLine(Xend, Yend, Xstart, Yend, color ,Line_width, LINE_STYLE_SOLID);
    }
}

/******************************************************************************
function:	Use the 8-point method to draw a circle of the
            specified size at the specified position->
parameter:
    X_Center  ：Center X coordinate
    Y_Center  ：Center Y coordinate
    Radius    ：circle Radius
    color     ：The color of the ：circle segment
    Filled    : Whether it is filled: 1 filling 0：Do not
******************************************************************************/
void GUI_DrawCircle(uint16_t X_Center, uint16_t Y_Center, uint16_t Radius, 
                        uint16_t color, DOT_PIXEL Line_width, DRAW_FILL Draw_Fill )
{
    //Draw a circle from(0, R) as a starting point
    int16_t XCurrent, YCurrent;
    XCurrent = 0;
    YCurrent = Radius;

    //Cumulative error,judge the next point of the logo
    int16_t Esp = 3 - (Radius << 1 );

    int16_t sCountY;
    if (Draw_Fill == DRAW_FILL_FULL) {
        while (XCurrent <= YCurrent ) { //Realistic circles
            for (sCountY = XCurrent; sCountY <= YCurrent; sCountY ++ ) {
                GUI_DrawPoint(X_Center + XCurrent, Y_Center + sCountY, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//1
                GUI_DrawPoint(X_Center - XCurrent, Y_Center + sCountY, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//2
                GUI_DrawPoint(X_Center - sCountY, Y_Center + XCurrent, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//3
                GUI_DrawPoint(X_Center - sCountY, Y_Center - XCurrent, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//4
                GUI_DrawPoint(X_Center - XCurrent, Y_Center - sCountY, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//5
                GUI_DrawPoint(X_Center + XCurrent, Y_Center - sCountY, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//6
                GUI_DrawPoint(X_Center + sCountY, Y_Center - XCurrent, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);//7
                GUI_DrawPoint(X_Center + sCountY, Y_Center + XCurrent, color, DOT_PIXEL_DFT, DOT_STYLE_DFT);
            }
            if (Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    } else { //Draw a hollow circle
        while (XCurrent <= YCurrent ) {
            GUI_DrawPoint(X_Center + XCurrent, Y_Center + YCurrent, color, Line_width, DOT_STYLE_DFT);//1
            GUI_DrawPoint(X_Center - XCurrent, Y_Center + YCurrent, color, Line_width, DOT_STYLE_DFT);//2
            GUI_DrawPoint(X_Center - YCurrent, Y_Center + XCurrent, color, Line_width, DOT_STYLE_DFT);//3
            GUI_DrawPoint(X_Center - YCurrent, Y_Center - XCurrent, color, Line_width, DOT_STYLE_DFT);//4
            GUI_DrawPoint(X_Center - XCurrent, Y_Center - YCurrent, color, Line_width, DOT_STYLE_DFT);//5
            GUI_DrawPoint(X_Center + XCurrent, Y_Center - YCurrent, color, Line_width, DOT_STYLE_DFT);//6
            GUI_DrawPoint(X_Center + YCurrent, Y_Center - XCurrent, color, Line_width, DOT_STYLE_DFT);//7
            GUI_DrawPoint(X_Center + YCurrent, Y_Center + XCurrent, color, Line_width, DOT_STYLE_DFT);//0

            if (Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 * (XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    }
}

/******************************************************************************
  function: Display image
  parameter:
    image            ：Image start address
    xStart           : X starting coordinates
    yStart           : Y starting coordinates
    xEnd             ：Image width
    yEnd             : Image height
******************************************************************************/
void GUI_DrawFrame(uint16_t xStart, uint16_t yStart, uint16_t W_Image, uint16_t H_Image)
{
  Hal_LCD_DrawImage(frame_buf, xStart, yStart, xStart + W_Image, yStart + H_Image);
}

#define TRAFFIC_LIGHT_HEIGHT 66
#define TRAFFIC_LIGHT_WIDTH  30

uint16_t tl_frame_buf[TRAFFIC_LIGHT_HEIGHT][TRAFFIC_LIGHT_WIDTH] = {0};

void GUI_TrafficLight_Init()
{
    Hal_LCD_ClearWindow(145, 12, 145 + TRAFFIC_LIGHT_WIDTH, 12 + TRAFFIC_LIGHT_HEIGHT, COLOR_TL_BG);
    Hal_LCD_ClearWindow(145, 160, 145 + TRAFFIC_LIGHT_WIDTH, 160 + TRAFFIC_LIGHT_HEIGHT, COLOR_TL_BG);
    Hal_LCD_ClearWindow(32, 104, 32 + TRAFFIC_LIGHT_HEIGHT, 104 + TRAFFIC_LIGHT_WIDTH, COLOR_TL_BG);
    Hal_LCD_ClearWindow(220, 104, 220 + TRAFFIC_LIGHT_HEIGHT, 104 + TRAFFIC_LIGHT_WIDTH, COLOR_TL_BG);

    GUI_DrawCircle(145 + 16, 12 + 15, 8, COLOR_TL_GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    GUI_DrawCircle(145 + 16, 12 + 15 + 19, 8, COLOR_TL_GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    GUI_DrawCircle(145 + 16, 12 + 15 + 19 + 19, 8, COLOR_TL_GRAY, DOT_PIXEL_1X1, DRAW_FILL_FULL);
}

void GUI_DrawBackground()
{
    Hal_LCD_Clear(COLOR_ROAD);

    Hal_LCD_ClearWindow(107, 0, 107, 75, BLACK);
    Hal_LCD_ClearWindow(213, 0, 213, 75, BLACK);
    Hal_LCD_ClearWindow(107, 160, 107, 240, BLACK);
    Hal_LCD_ClearWindow(213, 160, 213, 240, BLACK);

    Hal_LCD_ClearWindow(0, 76, 106, 76, BLACK);
    Hal_LCD_ClearWindow(214, 76, 320, 76, BLACK);
    Hal_LCD_ClearWindow(0, 159, 106, 159, BLACK);
    Hal_LCD_ClearWindow(214, 159, 320, 159, BLACK);

    Hal_LCD_ClearWindow(0, 0, 106, 75, COLOR_GRASS);
    Hal_LCD_ClearWindow(214, 0, 320, 75, COLOR_GRASS);
    Hal_LCD_ClearWindow(0, 160, 106, 240, COLOR_GRASS);
    Hal_LCD_ClearWindow(214, 160, 320, 240, COLOR_GRASS);
}

void GUI_Init()
{
    GUI_DrawBackground();
    GUI_TrafficLight_Init();
}