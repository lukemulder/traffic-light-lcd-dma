/*****************************************************************************
* | File      	:	hal_pwm.c
* | Author      :   Luke Mulder
* | Function    :   Hardware Access Layer (HAL) for Pulse Width Modulation Timers
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

#include "hal_pwm.h"

void HAL_PWM_InitTimer(uint32_t freq_hz, ledc_timer_bit_t duty_resolution) {
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = duty_resolution,
        .freq_hz = freq_hz,
        .speed_mode = LEDC_LOW_SPEED_MODE,  // Assuming low-speed mode is suitable for most uses
        .timer_num = LEDC_TIMER_0
    };
    ledc_timer_config(&ledc_timer);
}

void HAL_PWM_ConfigChannel(uint32_t duty, uint8_t channel, uint8_t gpio_pin) {
    ledc_channel_config_t ledc_channel = {
        .channel    = channel,
        .duty       = duty,
        .gpio_num   = gpio_pin,
        .speed_mode = LEDC_LOW_SPEED_MODE,  // Matching timer speed mode
        .timer_sel  = LEDC_TIMER_0
    };
    ledc_channel_config(&ledc_channel);
}