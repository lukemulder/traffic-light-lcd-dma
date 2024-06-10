/*****************************************************************************
* | File      	:	hal_button.h
* | Author      :   Luke Mulder
* | Function    :   Hardware Access Layer (HAL) for Buttons
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2024-05-24
* | Info        :   
#
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
#ifndef HAL_BUTTON_H
#define HAL_BUTTON_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#define BUTTON_TOP_BOTTOM_GPIO 26
#define BUTTON_LEFT_RIGHT_GPIO 25

#define BUTTON_ID_TOP_BOTTOM 1
#define BUTTON_ID_LEFT_RIGHT 2

#define BUTTON_QUEUE_LENGTH 2
#define BUTTON_QUEUE_ITEM_SIZE sizeof(int)

extern QueueHandle_t button_state_queue;

void Hal_Button_Init();

#endif