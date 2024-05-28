/*****************************************************************************
* | File      	:	hal_pwm.h
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
#ifndef _HAL_PWM_H_
#define _HAL_PWM_H_

#include "driver/ledc.h"

// Constants for PWM configuration
#define HAL_PWM_FREQ_HZ       5000
#define HAL_PWM_DUTY_CYCLE_50 128  // Duty cycle for 50% in 8-bit resolution

void HAL_PWM_InitTimer(uint32_t freq_hz, ledc_timer_bit_t duty_resolution);
void HAL_PWM_ConfigChannel(uint32_t duty, uint8_t channel, uint8_t gpio_pin);

#endif // HAL_PWM_H