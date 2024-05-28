/*****************************************************************************
* | File        :   hal_spi.c
* | Author      :   Luke Mulder
* | Function    :   HAL SPI Definitions
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

#include "hal_spi.h"
#include <string.h>

void Hal_SPI_Init(Hal_SPI_Config_t *cfg, Hal_SPI_Handle_t *h)
{
    spi_bus_config_t buscfg = {
        .mosi_io_num = cfg->pins.mosi,
        .miso_io_num = cfg->pins.miso, // MISO not used
        .sclk_io_num = cfg->pins.sclk,
        .quadwp_io_num = cfg->pins.quadwp,
        .quadhd_io_num = cfg->pins.quadhd,
        .max_transfer_sz = HAL_SPI_MAX_TRANSFER_SIZE
    };

    spi_device_interface_config_t devcfg = {
        .mode = 0,
        .clock_speed_hz = cfg->freq,
        .spics_io_num = cfg->pins.cs,
        .queue_size = HAL_SPI_QUEUE_SIZE,
    };

    // Initialize the SPI bus
    esp_err_t ret = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
    assert(ret == ESP_OK);

    // Attach the device to the SPI bus
    ret = spi_bus_add_device(SPI2_HOST, &devcfg, &(h->handle));
    assert(ret == ESP_OK);
}

/**
 * Hal SPI write byte
**/
HAL_ERR_T Hal_SPI_Transmit(Hal_SPI_Handle_t *h, uint8_t dat)
{
    if(h == NULL)
        return ESP_FAIL;

    spi_transaction_t t;

    //printf("%02X ", dat);

    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &dat;

    return spi_device_transmit(h->handle, &t);
}

/**
 * Hal SPI write buffer
**/
HAL_ERR_T Hal_SPI_Transmit_Buffer(Hal_SPI_Handle_t *h, const uint8_t *data, int size)
{
    if(h == NULL || data == NULL || size <= 0 || size > HAL_SPI_MAX_TRANSFER_SIZE)
        return ESP_FAIL;

    spi_transaction_t t;
/*
    for(int i = 0; i < size; i++)
    {
        printf("%02X ", data[i]);
    }
*/
    memset(&t, 0, sizeof(t));
    t.length = size * 8;
    t.tx_buffer = data;

    return spi_device_transmit(h->handle, &t);
}