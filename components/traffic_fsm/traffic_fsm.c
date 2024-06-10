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
#include "hal_button.h"
#include "hal_lcd.h"

void Traffic_FSM_Process_State()
{

}

void Traffic_FSM_Update_State()
{

}

void state_machine_task(void *params)
{
    int receivedState;

    while (1)
    {
        if (xQueueReceive(button_state_queue, &receivedState, portMAX_DELAY) == pdPASS)
        {
            // Process state change
            // Update state machine based on received state
            printf("Received button press!\n");
        }
    }
}

void Traffic_FSM_Task_Init()
{
    xTaskCreate(state_machine_task, "State Machine Task", 2048, NULL, 10, NULL);
}