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
        Hal_LCD_DrawImage(traffic_lights_green, 0, 0, TRAFFIC_LIGHTS_GREEN_WIDTH, TRAFFIC_LIGHTS_GREEN_HEIGHT);
        delay_ms(7000);
        Hal_LCD_DrawImage(traffic_lights_orange, 0, 0, TRAFFIC_LIGHTS_ORANGE_WIDTH, TRAFFIC_LIGHTS_ORANGE_HEIGHT);
        delay_ms(3000);
        Hal_LCD_DrawImage(traffic_lights_red, 0, 0, TRAFFIC_LIGHTS_RED_WIDTH, TRAFFIC_LIGHTS_RED_HEIGHT);
        delay_ms(7000);
    }
}