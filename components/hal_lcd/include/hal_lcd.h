/*****************************************************************************
* | File        :   hal_lcd.h
* | Author      :   Luke Mulder
* | Function    :   HAL Header for ST7789V LCD Controller
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* | This version:   V1.0
* | Date        :   2024-05-24
* | Info        :

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _HAL_LCD_H_
#define _HAL_LCD_H_

#include <stdint.h>

// LCD Pixel Dimensions
#define LCD_WIDTH  320
#define LCD_HEIGHT 240

/**
 * GPIO config
**/
#define LCD_DIN_PIN 23 // Data In or MOSI Pin
#define LCD_CLK_PIN 18 // Clock Signal Pin
#define LCD_CS_PIN  13 // Chip Select Pin
#define LCD_DC_PIN  22 // Data/Command Select Pin
#define LCD_RST_PIN 21 // Reset Pin
#define LCD_BL_PIN  2  // Back-light Pin

#define LCD_RST_PIN_ENABLE  0 // Active low reset
#define LCD_RST_PIN_DISABLE 1 

#define LCD_CS_PIN_ENABLE  0 // Active low chip select
#define LCD_CS_PIN_DISABLE 1

#define LCD_DC_PIN_DATA    1
#define LCD_DC_PIN_COMMAND 0

#define GPIO_DIGITAL_WRITE(_pin, _value) gpio_set_level(_pin, _value)

/**
 * delay x ms
**/
#define delay_ms(__xms) vTaskDelay(pdMS_TO_TICKS(__xms))

void Hal_LCD_Init(void);
void Hal_LCD_SetBackLight(uint8_t data);
void Hal_LCD_SetWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend);
void Hal_LCD_SetCursor(uint16_t X, uint16_t Y);
void Hal_LCD_Clear(uint16_t Color);
void Hal_LCD_ClearWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t color);
void Hal_LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void Hal_LCD_DrawImage(const void* img, uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend);

#endif // _HAL_LCD_H_