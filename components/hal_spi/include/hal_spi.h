/*****************************************************************************
* | File        :   hal_spi.h
* | Author      :   Luke Mulder
* | Function    :   HAL SPI Header
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
#ifndef _HAL_SPI_H_
#define _HAL_SPI_H_

#include "driver/spi_master.h"

#define HAL_SPI_PIN_EMPTY -1

typedef struct {
    int mosi;
    int miso;
    int sclk;
    int cs;
    int quadwp;
    int quadhd;
} Hal_SPI_Pin_Layout_t;

typedef struct {
    int freq;
    Hal_SPI_Pin_Layout_t pins;
} Hal_SPI_Config_t;

typedef struct {
    spi_device_handle_t handle;
} Hal_SPI_Handle_t;

#define HAL_ERR_T esp_err_t

#define HAL_SPI_MAX_TRANSFER_SIZE 4092
#define HAL_SPI_QUEUE_SIZE        7

#define HAL_SPI_FREQ_8MHZ  SPI_MASTER_FREQ_8M
#define HAL_SPI_FREQ_9MHZ  SPI_MASTER_FREQ_9M
#define HAL_SPI_FREQ_10MHZ SPI_MASTER_FREQ_10M
#define HAL_SPI_FREQ_11MHZ SPI_MASTER_FREQ_11M
#define HAL_SPI_FREQ_13MHZ SPI_MASTER_FREQ_13M
#define HAL_SPI_FREQ_16MHZ SPI_MASTER_FREQ_16M
#define HAL_SPI_FREQ_20MHZ SPI_MASTER_FREQ_20M
#define HAL_SPI_FREQ_26MHZ SPI_MASTER_FREQ_26M
#define HAL_SPI_FREQ_40MHZ SPI_MASTER_FREQ_40M
#define HAL_SPI_FREQ_80MHZ SPI_MASTER_FREQ_80M

void Hal_SPI_Init(Hal_SPI_Config_t *cfg, Hal_SPI_Handle_t *h);

HAL_ERR_T Hal_SPI_Transmit(Hal_SPI_Handle_t *h, uint8_t dat);
HAL_ERR_T Hal_SPI_Transmit_Buffer(Hal_SPI_Handle_t *h, const uint8_t *data, int size);

#endif // _HAL_SPI_H_