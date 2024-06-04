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
#include "GUI_Paint.h"
#include "image.h"
#include "animation.h"

void app_main(void)
{
    Hal_LCD_Init();
    /*
    delay_ms(5000);
    Hal_LCD_Clear(BLACK);
    delay_ms(5000);
    Hal_LCD_Clear(WHITE);
    delay_ms(2000);
    Hal_LCD_Clear(RED);       

    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
    */
    //Paint_DrawImage(gImage_70X70, 20, 80, 70, 70); 
    delay_ms(3000);
    /*
    while(1)
    {
        Paint_DrawImage((unsigned char*)frame_00_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_01_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_02_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_03_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_04_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_05_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_06_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_07_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_08_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_09_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_10_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_11_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_12_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_13_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_14_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_15_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_16_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_17_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_18_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_19_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_20_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);
        
        Paint_DrawImage((unsigned char*)frame_21_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_22_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);

        Paint_DrawImage((unsigned char*)frame_23_delay_0_06s, 0, 0, 169, 240);
        delay_ms(5);
        

    }
    */
}