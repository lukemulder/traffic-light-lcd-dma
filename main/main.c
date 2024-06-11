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
#include "traffic_fsm.h"
#include "hal_button.h"

void app_main(void)
{
    Hal_LCD_Init();
    Hal_Button_Init();
    
    Traffic_FSM_Task_Begin();
}