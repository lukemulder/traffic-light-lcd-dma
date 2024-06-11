/*****************************************************************************
* | File      	:	traffic_fsm.c
* | Author      :   Luke Mulder
* | Function    :   Finite State Machine to control the Traffic Intersection
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

#include "traffic_fsm.h"
#include "traffic_light_icons.h"
#include "gui_traffic_lights.h"
#include "esp_timer.h"
#include "hal_button.h"
#include "hal_lcd.h"

#define TIME_GREEN_WAIT_FOR_RED_SEC  1  * 1000 * 1000
#define TIME_MAX_ON_ORANGE_SEC       3  * 1000 * 1000
#define TIME_MAX_ON_GREEN_SEC        30 * 1000 * 1000
#define TIME_MIN_ON_GREEN_SEC        15 * 1000 * 1000

static TrafficLightState_t tl_state_top_bottom = {0};
static TrafficLightState_t tl_state_left_right = {0};

void Traffic_FSM_Update_State()
{
    uint64_t current_time = esp_timer_get_time();

    // Top Bottom Traffic Light State
    switch (tl_state_top_bottom.current_color)
    {
        case TL_RED:
            if(current_time - tl_state_top_bottom.time_on_color > TIME_MIN_ON_GREEN_SEC &&
                tl_state_left_right.current_color == TL_RED &&
               (current_time - tl_state_left_right.time_on_color > TIME_GREEN_WAIT_FOR_RED_SEC))
            {
                tl_state_top_bottom.current_color = TL_GREEN;
                tl_state_top_bottom.time_on_color = current_time;

                GUI_TrafficLight_Set(TRAFFIC_LIGHT_TOP, TRAFFIC_LIGHT_COLOR_GREEN);
                GUI_TrafficLight_Set(TRAFFIC_LIGHT_BOTTOM, TRAFFIC_LIGHT_COLOR_GREEN);
            }
            break;
        case TL_GREEN:
            if((current_time - tl_state_top_bottom.time_on_color > TIME_MAX_ON_GREEN_SEC) ||
                (current_time - tl_state_top_bottom.time_on_color > TIME_MIN_ON_GREEN_SEC &&
                tl_state_left_right.pedestrianButtonPressed))
            {
                tl_state_top_bottom.current_color = TL_ORANGE;
                tl_state_top_bottom.time_on_color = current_time;

                GUI_TrafficLight_Set(TRAFFIC_LIGHT_TOP, TRAFFIC_LIGHT_COLOR_ORANGE);
                GUI_TrafficLight_Set(TRAFFIC_LIGHT_BOTTOM, TRAFFIC_LIGHT_COLOR_ORANGE);
            }
            break;
        case TL_ORANGE:
            if(current_time - tl_state_top_bottom.time_on_color > TIME_MAX_ON_ORANGE_SEC)
            {
                tl_state_top_bottom.current_color = TL_RED;
                tl_state_top_bottom.time_on_color = current_time;
                tl_state_left_right.pedestrianButtonPressed = 0;

                GUI_TrafficLight_Set(TRAFFIC_LIGHT_TOP, TRAFFIC_LIGHT_COLOR_RED);
                GUI_TrafficLight_Set(TRAFFIC_LIGHT_BOTTOM, TRAFFIC_LIGHT_COLOR_RED);
            }
            break;
        case TL_OFF:
            tl_state_top_bottom.current_color = TL_RED;
            tl_state_top_bottom.time_on_color = current_time;
            tl_state_left_right.pedestrianButtonPressed = 0;

            GUI_TrafficLight_Set(TRAFFIC_LIGHT_TOP, TRAFFIC_LIGHT_COLOR_RED);
            GUI_TrafficLight_Set(TRAFFIC_LIGHT_BOTTOM, TRAFFIC_LIGHT_COLOR_RED);
            break;
    }

    // Left Right Traffic Light State
    switch (tl_state_left_right.current_color)
    {
        case TL_RED:
            if(current_time - tl_state_left_right.time_on_color > TIME_MIN_ON_GREEN_SEC &&
                tl_state_top_bottom.current_color == TL_RED &&
               (current_time - tl_state_top_bottom.time_on_color > TIME_GREEN_WAIT_FOR_RED_SEC))
            {
                tl_state_left_right.current_color = TL_GREEN;
                tl_state_left_right.time_on_color = current_time;

                GUI_TrafficLight_Set(TRAFFIC_LIGHT_LEFT, TRAFFIC_LIGHT_COLOR_GREEN);
                GUI_TrafficLight_Set(TRAFFIC_LIGHT_RIGHT, TRAFFIC_LIGHT_COLOR_GREEN);
            }
            break;
        case TL_GREEN:
            if((current_time - tl_state_left_right.time_on_color > TIME_MAX_ON_GREEN_SEC) ||
                (current_time - tl_state_left_right.time_on_color > TIME_MIN_ON_GREEN_SEC &&
                tl_state_top_bottom.pedestrianButtonPressed))
            {
                tl_state_left_right.current_color = TL_ORANGE;
                tl_state_left_right.time_on_color = current_time;

                GUI_TrafficLight_Set(TRAFFIC_LIGHT_LEFT, TRAFFIC_LIGHT_COLOR_ORANGE);
                GUI_TrafficLight_Set(TRAFFIC_LIGHT_RIGHT, TRAFFIC_LIGHT_COLOR_ORANGE);
            }
            break;
        case TL_ORANGE:
            if(current_time - tl_state_left_right.time_on_color > TIME_MAX_ON_ORANGE_SEC)
            {
                tl_state_left_right.current_color = TL_RED;
                tl_state_left_right.time_on_color = current_time;
                tl_state_top_bottom.pedestrianButtonPressed = 0;

                GUI_TrafficLight_Set(TRAFFIC_LIGHT_LEFT, TRAFFIC_LIGHT_COLOR_RED);
                GUI_TrafficLight_Set(TRAFFIC_LIGHT_RIGHT, TRAFFIC_LIGHT_COLOR_RED);
            }
            break;
        case TL_OFF:
            tl_state_left_right.current_color = TL_RED;
            tl_state_left_right.time_on_color = current_time;
            tl_state_top_bottom.pedestrianButtonPressed = 0;

            GUI_TrafficLight_Set(TRAFFIC_LIGHT_LEFT, TRAFFIC_LIGHT_COLOR_RED);
            GUI_TrafficLight_Set(TRAFFIC_LIGHT_RIGHT, TRAFFIC_LIGHT_COLOR_RED);
            break;
    }
}

void traffic_fsm_task(void *params)
{
    int receivedButtonID;

    for(;;)
    {
        if (xQueueReceive(button_state_queue, &receivedButtonID, 0) == pdPASS)
        {
            if (receivedButtonID == BUTTON_ID_TOP_BOTTOM) {
                tl_state_top_bottom.pedestrianButtonPressed = 1;
                printf("Top/bottom button pressed!\n");
            } else if (receivedButtonID == BUTTON_ID_LEFT_RIGHT) {
                tl_state_left_right.pedestrianButtonPressed = 1;
                printf("Left/right button pressed!\n");
            }
        }

        Traffic_FSM_Update_State();

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void Traffic_FSM_Task_Begin()
{
    GUI_Init();

    // Place traffic lights in known state
    GUI_TrafficLight_Set(TRAFFIC_LIGHT_TOP, TRAFFIC_LIGHT_COLOR_GREEN);
    GUI_TrafficLight_Set(TRAFFIC_LIGHT_BOTTOM, TRAFFIC_LIGHT_COLOR_GREEN);

    GUI_TrafficLight_Set(TRAFFIC_LIGHT_LEFT, TRAFFIC_LIGHT_COLOR_RED);
    GUI_TrafficLight_Set(TRAFFIC_LIGHT_RIGHT, TRAFFIC_LIGHT_COLOR_RED);

    uint64_t current_time = esp_timer_get_time();
    tl_state_top_bottom.time_on_color = current_time;
    tl_state_left_right.time_on_color = current_time;

    tl_state_top_bottom.current_color = TL_GREEN;
    tl_state_left_right.current_color = TL_RED;

    // Create task to handle state machine
    xTaskCreate(traffic_fsm_task, "Traffic Light SM Task", 2048, NULL, 10, NULL);
}