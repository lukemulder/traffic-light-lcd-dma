/*****************************************************************************
* | File      	:	hal_button.c
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

#include "hal_button.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include <stdint.h>

QueueHandle_t button_state_queue = NULL;
static int buttonIDs[] = {BUTTON_ID_TOP_BOTTOM, BUTTON_ID_LEFT_RIGHT};

static void IRAM_ATTR isr_button_handler(void* arg) {
    int buttonID = *(int*)arg;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    static uint64_t last_interrupt_time[TOTAL_BUTTONS] = {0};
    uint64_t interrupt_time = esp_timer_get_time();

    // Debounce with 200ms
    if (interrupt_time - last_interrupt_time[buttonID] > 200000) {
        xQueueSendFromISR(button_state_queue, &buttonID, &xHigherPriorityTaskWoken);
        last_interrupt_time[buttonID] = interrupt_time;
    }

    // Yield if a higher priority task was woken
    if (xHigherPriorityTaskWoken) {
        portYIELD_FROM_ISR();
    }
}

void Hal_Button_GPIO_ISR_Init(gpio_num_t gpio_num, gpio_isr_t isr_handler, void* arg)
{
    gpio_config_t io_conf;
    // Disable interrupts
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    // Set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    // Enable pull-up resistor
    io_conf.pull_up_en = 1;
    io_conf.pull_down_en = 0;
    // Configure the GPIO pin
    io_conf.pin_bit_mask = (1ULL << gpio_num);
    gpio_config(&io_conf);

    // Attach the interrupt service routine
    gpio_isr_handler_add(gpio_num, isr_handler, arg);
}

void Hal_Button_Init() {
    // Install GPIO ISR service
    gpio_install_isr_service(ESP_INTR_FLAG_LEVEL1);

    // Initialize ISRs for each button
    Hal_Button_GPIO_ISR_Init(BUTTON_TOP_BOTTOM_GPIO, isr_button_handler, &buttonIDs[0]);
    Hal_Button_GPIO_ISR_Init(BUTTON_LEFT_RIGHT_GPIO, isr_button_handler, &buttonIDs[1]);

    // Create a queue to hold button states
    button_state_queue = xQueueCreate(BUTTON_QUEUE_LENGTH, BUTTON_QUEUE_ITEM_SIZE);

    if (button_state_queue == NULL) {
        // Handle error: Failed to create the queue
    }
}