/******************************************************************************
* | File      	:   gui_traffic_lights.h
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
#ifndef __GUI_PAINT_H
#define __GUI_PAINT_H

#include "logging.h"
#include <stdint.h>

/**
 * image color
**/
#define WHITE         0xFFFF
#define BLACK         0x0000
#define BLUE          0x001F
#define GBLUE         0X07FF
#define RED           0xF800
#define MAGENTA       0xF81F
#define GREEN         0x07E0
#define CYAN          0x7FFF
#define YELLOW        0xFFE0
#define BROWN         0XBC40
#define GRAY          0X8430

#define COLOR_ROAD 0x8C71
#define COLOR_GRASS 0x44C8

#define IMAGE_BACKGROUND COLOR_ROAD

/**
 * The size of the point
**/
typedef enum {
    DOT_PIXEL_1X1  = 1,   // 1 x 1
    DOT_PIXEL_2X2  ,    // 2 X 2
    DOT_PIXEL_3X3  ,    // 3 X 3
    DOT_PIXEL_4X4  ,    // 4 X 4
    DOT_PIXEL_5X5  ,    // 5 X 5
    DOT_PIXEL_6X6  ,    // 6 X 6
    DOT_PIXEL_7X7  ,    // 7 X 7
    DOT_PIXEL_8X8  ,    // 8 X 8
} DOT_PIXEL;
#define DOT_PIXEL_DFT  DOT_PIXEL_1X1  //Default dot pilex

/**
 * Point size fill style
**/
typedef enum {
    DOT_FILL_AROUND  = 1,   // dot pixel 1 x 1
    DOT_FILL_RIGHTUP  ,     // dot pixel 2 X 2
} DOT_STYLE;
#define DOT_STYLE_DFT  DOT_FILL_AROUND  //Default dot pilex

/**
 * Line style, solid or dashed
**/
typedef enum {
    LINE_STYLE_SOLID = 0,
    LINE_STYLE_DOTTED,
} LINE_STYLE;

/**
 * Rotation to be applied to an image during rendering
**/
typedef enum {
    DEGREES_0 = 0,
    DEGREES_90,
    DEGREES_180,
    DEGREES_270
} ROTATION;

/**
 * Index for selecting each of the traffic lights
**/
typedef enum {
    TRAFFIC_LIGHT_TOP = 0,
    TRAFFIC_LIGHT_BOTTOM,
    TRAFFIC_LIGHT_LEFT,
    TRAFFIC_LIGHT_RIGHT
} TRAFFIC_LIGHT_INDEX_e;

/**
 * Used to select the indicator to be displayed by a traffic light
**/
typedef enum {
    TRAFFIC_LIGHT_COLOR_OFF = 0,
    TRAFFIC_LIGHT_COLOR_GREEN,
    TRAFFIC_LIGHT_COLOR_ORANGE,
    TRAFFIC_LIGHT_COLOR_RED
} TRAFFIC_LIGHT_COLOR_e;

/**
 * Starting coordinates of the 4 traffic lights
**/
#define TRAFFIC_LIGHT_TOP_X    145
#define TRAFFIC_LIGHT_TOP_Y    12
#define TRAFFIC_LIGHT_BOTTOM_X 145
#define TRAFFIC_LIGHT_BOTTOM_Y 160
#define TRAFFIC_LIGHT_LEFT_X   220
#define TRAFFIC_LIGHT_LEFT_Y   104
#define TRAFFIC_LIGHT_RIGHT_X  32
#define TRAFFIC_LIGHT_RIGHT_Y  104

/**
 * Whether the graphic is filled
**/
typedef enum {
    DRAW_FILL_EMPTY = 0,
    DRAW_FILL_FULL,
} DRAW_FILL;

// Init and Clear
void GUI_Init();
void GUI_Clear(uint16_t Color);

// Drawing
void GUI_DrawPoint(uint16_t Xpoint, uint16_t Ypoint, uint16_t Color, DOT_PIXEL Dot_Pixel, DOT_STYLE Dot_FillWay);
void GUI_DrawLine(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color, DOT_PIXEL Line_width, LINE_STYLE Line_Style);
void GUI_DrawRectangle(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color, DOT_PIXEL Line_width, DRAW_FILL Filled );
int GUI_DrawImage(const void* img, uint16_t xStart, uint16_t yStart, uint16_t W_Image, uint16_t H_Image, ROTATION r);

// Traffic Light
void GUI_TrafficLight_Set(TRAFFIC_LIGHT_INDEX_e tl_index, TRAFFIC_LIGHT_COLOR_e tl_color);

void GUI_TrafficLight_Init();
void GUI_DrawBackground();

#endif
