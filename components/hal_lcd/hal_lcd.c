/*****************************************************************************
* | File      	:	hal_lcd.c
* | Author      :   Luke Mulder
* | Function    :   Hardware Access Layer (HAL) for ST7789V Controller
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

#include "hal_lcd.h"
#include "hal_lcd_types.h"

#include "hal_spi.h"
#include "hal_gpio.h"
#include "hal_pwm.h"

Hal_SPI_Handle_t lcd_spi_handle;

static void HAL_LCD_GPIO_Init()
{
    HAL_GPIO_SET_PIN_MODE(LCD_DIN_PIN, GPIO_MODE_OUTPUT);
    HAL_GPIO_SET_PIN_MODE(LCD_CS_PIN, GPIO_MODE_OUTPUT);
    HAL_GPIO_SET_PIN_MODE(LCD_RST_PIN, GPIO_MODE_OUTPUT);
    HAL_GPIO_SET_PIN_MODE(LCD_DC_PIN, GPIO_MODE_OUTPUT);
    HAL_GPIO_SET_PIN_MODE(LCD_BL_PIN, GPIO_MODE_OUTPUT);

    HAL_PWM_InitTimer(HAL_PWM_FREQ_HZ, LEDC_TIMER_8_BIT);
    HAL_PWM_ConfigChannel(HAL_PWM_DUTY_CYCLE_50, LEDC_CHANNEL_0, LCD_BL_PIN);
}

/*******************************************************************************
function:
	LCD Hardware Reset
*******************************************************************************/
static void Hal_LCD_SPI_Init(void)
{
    Hal_SPI_Config_t cfg = {
        .freq        = HAL_SPI_FREQ_20MHZ,
        .pins.mosi   = LCD_DIN_PIN,
        .pins.miso   = HAL_SPI_PIN_EMPTY,
        .pins.sclk   = LCD_CLK_PIN,
        .pins.cs     = LCD_CS_PIN,
        .pins.quadwp = HAL_SPI_PIN_EMPTY,
        .pins.quadhd = HAL_SPI_PIN_EMPTY
    };

    Hal_SPI_Init(&cfg, &lcd_spi_handle);
}

/*******************************************************************************
function:
	LCD Hardware Reset
*******************************************************************************/
static void Hal_LCD_Reset(void)
{
    GPIO_DIGITAL_WRITE(LCD_RST_PIN, LCD_RST_PIN_ENABLE);
    delay_ms(1);  // Apply reset pulse longer than 10 microseconds
    GPIO_DIGITAL_WRITE(LCD_RST_PIN, LCD_RST_PIN_DISABLE);
    
    // Delay to ensure reset completion and NVM loading
    delay_ms(5);
}

/*******************************************************************************
function: 
	Write command and associated data
*******************************************************************************/
static void Hal_LCD_Data_Write(const void *data, int data_len)	 
{
    if(data == NULL || data_len <= 0) { return; }

	GPIO_DIGITAL_WRITE(LCD_CS_PIN, LCD_CS_PIN_ENABLE);
    GPIO_DIGITAL_WRITE(LCD_DC_PIN, LCD_DC_PIN_DATA);

    int num_transactions = (data_len + HAL_SPI_MAX_TRANSFER_SIZE - 1) / HAL_SPI_MAX_TRANSFER_SIZE;
    uint16_t t_len;
    int offset = 0;

    for(int i = 0; i < num_transactions; i++)
    {
        t_len = (data_len < HAL_SPI_MAX_TRANSFER_SIZE) ? data_len : HAL_SPI_MAX_TRANSFER_SIZE;
        Hal_SPI_Transmit_Buffer(&lcd_spi_handle, data + offset, t_len);

        data_len -= t_len;
        offset += t_len;
    }
    
	GPIO_DIGITAL_WRITE(LCD_CS_PIN, LCD_CS_PIN_DISABLE);
}

/*******************************************************************************
function: 
	Write command and associated data
*******************************************************************************/
static void Hal_LCD_Command_Write_Data(uint8_t cmd, void *data, int data_len)
{
    GPIO_DIGITAL_WRITE(LCD_CS_PIN, LCD_CS_PIN_ENABLE);
    GPIO_DIGITAL_WRITE(LCD_DC_PIN, LCD_DC_PIN_COMMAND);

    Hal_SPI_Transmit(&lcd_spi_handle, cmd);

    if(data != NULL && data_len > 0)
    {
        Hal_LCD_Data_Write(data, data_len);
    }
    
    GPIO_DIGITAL_WRITE(LCD_CS_PIN, LCD_CS_PIN_DISABLE);
}

/*******************************************************************************
function:
		Write commands
*******************************************************************************/
static void Hal_LCD_Command_Write(uint8_t cmd)	 
{	
    Hal_LCD_Command_Write_Data(cmd, NULL, 0);
}

/******************************************************************************
function:	
		Common register initialization
******************************************************************************/
void Hal_LCD_Init(void)
{
    HAL_LCD_GPIO_Init();
    Hal_LCD_SPI_Init();

	Hal_LCD_Reset();

    HAL_LCD_MADCTL_REG_t madctl_reg = {0};
    //madctl_reg.regs.MY = 1;
    //madctl_reg.regs.MV = 1;
    madctl_reg.data = 0xA0;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_M_ACCESS_CTL, &madctl_reg, sizeof(madctl_reg));

    HAL_LCD_COLMOD_REG_t colmod_reg = {0};
    //colmod_reg.regs.CTRL_INTF_CL_FORMAT = COLMOD_CTRL_16B_PER_PIXEL;
    colmod_reg.data = 0x05;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_COL_MODE, &colmod_reg, sizeof(colmod_reg));

    Hal_LCD_Command_Write(LCD_CMD_ADDR_INV_ON);

    HAL_LCD_CASET_REG_t caset_reg = {0};
    //caset_reg.regs.COL_START = 0x0000;
    //caset_reg.regs.COL_END = 0x013F;
    caset_reg.data[0] = 0x00;
    caset_reg.data[1] = 0x00;
    caset_reg.data[2] = 0x01;
    caset_reg.data[3] = 0x3F;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_COL_ADDR_SET, &caset_reg, sizeof(caset_reg));

    HAL_LCD_RASET_REG_t raset_reg = {0};
    //raset_reg.regs.ROW_START = 0x0000;
    //raset_reg.regs.ROW_END = 0x00EF;
    raset_reg.data[0] = 0x00;
    raset_reg.data[1] = 0x00;
    raset_reg.data[2] = 0x00;
    raset_reg.data[3] = 0xEF;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_ROW_ADDR_SET, &raset_reg, sizeof(raset_reg));

    HAL_LCD_PORCTRL_REG_t porch_reg = {0};
    //porch_reg.regs.BPA = 0xC;
    //porch_reg.regs.FPA = 0xC;
    //porch_reg.regs.PSEN = 0;
    //porch_reg.regs.BPB = 0x3;
    //porch_reg.regs.FPB = 0x3;
    //porch_reg.regs.BPC = 0x3;
    //porch_reg.regs.FPC = 0x3;
    porch_reg.data[0] = 0x0C;
    porch_reg.data[1] = 0x0C;
    porch_reg.data[2] = 0x00;
    porch_reg.data[3] = 0x33;
    porch_reg.data[4] = 0x33;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_PORCH_CTRL, &porch_reg, sizeof(porch_reg));

    HAL_LCD_GCTRL_REG_t gctrl_reg = {0};
    //gctrl_reg.regs.VGHS = GCTRL_VGH_13_26V;
    //gctrl_reg.regs.VGLS = GCTRL_VGL_NEG_10_43V;
    gctrl_reg.data = 0x35;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_GATE_V_CTRL, &gctrl_reg, sizeof(gctrl_reg));

    HAL_LCD_VCOMS_REG_t vcom_reg = {0};
    //vcom_reg.regs.VCOM = 0x1F; // 0.875V
    vcom_reg.data = 0x1F;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_VCOM_SET, &vcom_reg, sizeof(vcom_reg));

    HAL_LCD_LCMCTRL_REG_t lcmctrl_reg = {0};
    //lcmctrl_reg.regs.XMY = 0;
    //lcmctrl_reg.regs.XBGR = 1;
    //lcmctrl_reg.regs.XINV = 0;
    //lcmctrl_reg.regs.XMX = 1;
    //lcmctrl_reg.regs.XMH = 1;
    //lcmctrl_reg.regs.XMV = 0;
    //lcmctrl_reg.regs.XGS = 0;
    lcmctrl_reg.data = 0x2C;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_LCM_CTRL, &lcmctrl_reg, sizeof(lcmctrl_reg));

    HAL_LCD_VDVVRHEN_REG_t vdvvrhen_reg = {0};
    //vdvvrhen_reg.regs.CMDEN = VDVVRHEN_SET_REG_FROM_CMD_WR;
    vdvvrhen_reg.data = 0x01;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_VDV_VRH_EN, &vdvvrhen_reg, sizeof(vdvvrhen_reg));

    HAL_LCD_VRHS_REG_t vrhs_reg = {0};
    //vrhs_reg.regs.VRHS = 0x12; // 4.45V + (vcom + vcom_offset + vdv)
    vrhs_reg.data = 0x12;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_VRH_SET, &vrhs_reg, sizeof(vrhs_reg));

    HAL_LCD_VDVS_REG_t vdvs_reg = {0};
    //vdvs_reg.regs.VDVS = 0x20; // 0V
    vdvs_reg.data = 0x20;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_VDV_SET, &vdvs_reg, sizeof(vdvs_reg));

    HAL_LCD_FRCTRL2_REG_t frctrl2_reg = {0};
    //frctrl2_reg.regs.NLA = 0x0; // Dot inversion
    //frctrl2_reg.regs.RTNA = 0xF; // 60Hz
    frctrl2_reg.data = 0x0F;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_FR_CTRL_2, &frctrl2_reg, sizeof(frctrl2_reg));

    HAL_LCD_PWCTRL1_REG_t pwctrl1_reg = {0};
    //pwctrl1_reg.regs.DEFAULT = 0xA4; // Default must be written
    //pwctrl1_reg.regs.AVDD = AVDD_6_8V;
    //pwctrl1_reg.regs.AVCL = AVCL_NEG_4_8V;
    //pwctrl1_reg.regs.VDS = VDS_2_3V;
    pwctrl1_reg.data[0] = 0xA4;
    pwctrl1_reg.data[1] = 0xA1;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_PW_CTRL_1, &pwctrl1_reg, sizeof(pwctrl1_reg));

    HAL_LCD_PVGAMCTRL_REG_t pvgamctrl_reg;
    pvgamctrl_reg.data[0] = 0xD0;
    pvgamctrl_reg.data[1] = 0x08;
    pvgamctrl_reg.data[2] = 0x11;
    pvgamctrl_reg.data[3] = 0x08;
    pvgamctrl_reg.data[4] = 0x0C;
    pvgamctrl_reg.data[5] = 0x15;
    pvgamctrl_reg.data[6] = 0x39;
    pvgamctrl_reg.data[7] = 0x33;
    pvgamctrl_reg.data[8] = 0x50;
    pvgamctrl_reg.data[9] = 0x36;
    pvgamctrl_reg.data[10] = 0x13;
    pvgamctrl_reg.data[11] = 0x14;
    pvgamctrl_reg.data[12] = 0x29;
    pvgamctrl_reg.data[13] = 0x2D;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_POS_V_GAM_CTL, &pvgamctrl_reg, sizeof(pvgamctrl_reg));

    HAL_LCD_NVGAMCTRL_REG_t nvgamctrl_reg;
	nvgamctrl_reg.data[0] = 0xD0;
	nvgamctrl_reg.data[1] = 0x08;
	nvgamctrl_reg.data[2] = 0x10;
	nvgamctrl_reg.data[3] = 0x08;
	nvgamctrl_reg.data[4] = 0x06;
	nvgamctrl_reg.data[5] = 0x06;
	nvgamctrl_reg.data[6] = 0x39;
	nvgamctrl_reg.data[7] = 0x44;
	nvgamctrl_reg.data[8] = 0x51;
	nvgamctrl_reg.data[9] = 0x0B;
	nvgamctrl_reg.data[10] = 0x16;
	nvgamctrl_reg.data[11] = 0x14;
	nvgamctrl_reg.data[12] = 0x2F;
	nvgamctrl_reg.data[13] = 0x31;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_NEG_V_GAM_CTL, &nvgamctrl_reg, sizeof(nvgamctrl_reg));

	Hal_LCD_Command_Write(LCD_CMD_ADDR_INV_ON);
	Hal_LCD_Command_Write(LCD_CMD_ADDR_SLP_OUT);
	Hal_LCD_Command_Write(LCD_CMD_ADDR_DISP_ON);
}

/******************************************************************************
function:	Toggle the backlight (0 off | >0 on)
parameter	:
	    data: 	Setting of the screen backlight
******************************************************************************/
void Hal_LCD_SetBackLight(uint8_t data)
{
	GPIO_DIGITAL_WRITE(LCD_BL_PIN, data);
}

/******************************************************************************
function:	Set the cursor position
parameter	:
	  Xstart: 	Start uint16_t x coordinate
	  Ystart:	Start uint16_t y coordinate
	  Xend  :	End uint16_t coordinates
	  Yend  :	End uint16_t coordinatesen
******************************************************************************/
void Hal_LCD_SetWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
    HAL_LCD_CASET_REG_t caset_reg = {0};
    //caset_reg.regs.COL_START = Xstart;
    //caset_reg.regs.COL_END = Xend;
    caset_reg.data[0] = Xstart >> 8;
    caset_reg.data[1] = Xstart & 0xFF;
    caset_reg.data[2] = Xend >> 8;
    caset_reg.data[3] = Xend & 0xFF;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_COL_ADDR_SET, &caset_reg, sizeof(caset_reg));

    HAL_LCD_RASET_REG_t raset_reg = {0};
    //raset_reg.regs.ROW_START = Ystart;
    //raset_reg.regs.ROW_END = Yend;
    raset_reg.data[0] = Ystart >> 8;
    raset_reg.data[1] = Ystart & 0xFF;
    raset_reg.data[2] = Yend >> 8;
    raset_reg.data[3] = Yend & 0xFF;
	Hal_LCD_Command_Write_Data(LCD_CMD_ADDR_ROW_ADDR_SET, &raset_reg, sizeof(raset_reg));
}

/******************************************************************************
function:	Settings window
parameter	:
	  Xstart: 	Start uint16_t x coordinate
	  Ystart:	Start uint16_t y coordinate

******************************************************************************/
void Hal_LCD_SetCursor(uint16_t X, uint16_t Y)
{ 
    Hal_LCD_SetWindow(X, Y, X, Y);
}

/******************************************************************************
function:	Refresh a certain area to the same color
parameter	:
	  Xstart: Start uint16_t x coordinate
	  Ystart:	Start uint16_t y coordinate
	  Xend  :	End uint16_t coordinates
	  Yend  :	End uint16_t coordinates
	  color :	Set the color
******************************************************************************/
void Hal_LCD_ClearWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t color)
{
    if(Xstart > Xend || Ystart > Yend) { return; }

	int i;
    int windowXSize = Xend - Xstart + 1;
    int windowYSize = Yend - Ystart + 1;

    int col_buf_size = windowYSize*2;
    uint8_t* colBuffer = malloc(col_buf_size * sizeof(uint8_t));
    if (colBuffer == NULL) { return; }

    for (i = 0; i < col_buf_size; i += 2) {
        colBuffer[i] = (color >> 8) & 0xFF;
        colBuffer[i + 1] = color & 0xFF;
    }

	Hal_LCD_SetWindow(Xstart, Ystart, Xend, Yend);
    Hal_LCD_Command_Write(LCD_CMD_ADDR_ROW_ADDR_MWR);

    // Send each line separately
    for(i = 0; i < windowXSize; i++)
    {
        Hal_LCD_Data_Write(colBuffer, col_buf_size);
    }

    free(colBuffer);
}

/******************************************************************************
function:	Clear screen function, refresh the screen to a certain color
parameter	:
	  Color :		The color you want to clear all the screen
******************************************************************************/
void Hal_LCD_Clear(uint16_t color)
{
    Hal_LCD_ClearWindow(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, color);
}

/******************************************************************************
function: Draw a point
parameter	:
	    X	: 	Set the X coordinate
	    Y	:	Set the Y coordinate
	  Color :	Set the color
******************************************************************************/
void Hal_LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	Hal_LCD_SetCursor(x, y);
    Hal_LCD_Command_Write(LCD_CMD_ADDR_ROW_ADDR_MWR);
	Hal_LCD_Data_Write(&color, sizeof(color));    
}

/******************************************************************************
function: Draw a point
parameter	:
	    X	: 	Set the X coordinate
	    Y	:	Set the Y coordinate
	  Color :	Set the color
******************************************************************************/
void Hal_LCD_DrawImage(const void* img, uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
    if(Xstart > Xend || Ystart > Yend || img == NULL)
    {
        
        return; 
    }

    int img_size = (Xstart - Xend) * (Ystart - Yend) * 2;

    Hal_LCD_SetWindow(Xstart, Ystart, Xend, Yend);
    Hal_LCD_Command_Write(LCD_CMD_ADDR_ROW_ADDR_MWR);
    Hal_LCD_Data_Write(img, img_size);
}
