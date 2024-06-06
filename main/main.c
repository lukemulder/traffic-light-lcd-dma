/*****************************************************************************
* | File        : main.c
* | Author      : Luke Mulder
* | Function    : Traffic Light Control
* | Info        :
*   Implements a traffic light with a finite state machine and displays it to
*   an LCD diaply.
******************************************************************************/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal_lcd.h"
#include "traffic_light_icons.h"
#include "gui_traffic_lights.h"

void app_main(void)
{
    Hal_LCD_Init();
    GUI_Init();

    while(1)
    {
        GUI_TrafficLight_Set(TRAFFIC_LIGHT_LEFT, TRAFFIC_LIGHT_COLOR_RED);
        GUI_TrafficLight_Set(TRAFFIC_LIGHT_RIGHT, TRAFFIC_LIGHT_COLOR_RED);
        delay_ms(1000);

        GUI_TrafficLight_Set(TRAFFIC_LIGHT_TOP, TRAFFIC_LIGHT_COLOR_GREEN);
        GUI_TrafficLight_Set(TRAFFIC_LIGHT_BOTTOM, TRAFFIC_LIGHT_COLOR_GREEN);
        delay_ms(7000);

        GUI_TrafficLight_Set(TRAFFIC_LIGHT_TOP, TRAFFIC_LIGHT_COLOR_ORANGE);
        GUI_TrafficLight_Set(TRAFFIC_LIGHT_BOTTOM, TRAFFIC_LIGHT_COLOR_ORANGE);
        delay_ms(3000);

        GUI_TrafficLight_Set(TRAFFIC_LIGHT_TOP, TRAFFIC_LIGHT_COLOR_RED);
        GUI_TrafficLight_Set(TRAFFIC_LIGHT_BOTTOM, TRAFFIC_LIGHT_COLOR_RED);
        delay_ms(1000);
        
        GUI_TrafficLight_Set(TRAFFIC_LIGHT_LEFT, TRAFFIC_LIGHT_COLOR_GREEN);
        GUI_TrafficLight_Set(TRAFFIC_LIGHT_RIGHT, TRAFFIC_LIGHT_COLOR_GREEN);
        delay_ms(4000);

        GUI_TrafficLight_Set(TRAFFIC_LIGHT_LEFT, TRAFFIC_LIGHT_COLOR_ORANGE);
        GUI_TrafficLight_Set(TRAFFIC_LIGHT_RIGHT, TRAFFIC_LIGHT_COLOR_ORANGE);
        delay_ms(3000);

    }
}