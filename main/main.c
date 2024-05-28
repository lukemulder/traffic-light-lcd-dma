#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "hal_lcd.h"
#include "GUI_Paint.h"
#include "image.h"
#include "animation.h"
#include "esp_log.h"
#include "driver/uart.h"

void app_main(void)
{

  //runLengthEncode((uint8_t*)frame_00_delay_0_06s, 169*240*2);
  Hal_LCD_Init();
  delay_ms(5000);
  //LCD_Clear(WHITE);
  //LCD_Clear(RED);
  //LCD_Clear(GREEN);
  Hal_LCD_Clear(BLACK);
  //Hal_LCD_DrawPoint(1, 1, WHITE);

  delay_ms(5000);
  Hal_LCD_Clear(WHITE);
  delay_ms(2000);
  Hal_LCD_Clear(RED);
/*
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);

  Hal_LCD_Clear(BLACK);

  Paint_DrawString_EN(30, 10, "123", &Font24, YELLOW, RED);
  Paint_DrawString_EN(30, 34, "ABC", &Font24, BLUE, CYAN);
  
  Paint_DrawRectangle(125, 10, 225, 58, RED,  DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
  Paint_DrawLine(125, 10, 225, 58, MAGENTA,   DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  Paint_DrawLine(225, 10, 125, 58, MAGENTA,   DOT_PIXEL_2X2,LINE_STYLE_SOLID);
  
  Paint_DrawCircle(150,100, 25, BLUE,   DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  Paint_DrawCircle(180,100, 25, BLACK,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  Paint_DrawCircle(210,100, 25, RED,    DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  Paint_DrawCircle(165,125, 25, YELLOW, DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  Paint_DrawCircle(195,125, 25, GREEN,  DOT_PIXEL_2X2,   DRAW_FILL_EMPTY);
  
  

  //Paint_DrawImage(gImage_70X70, 20, 80, 70, 70); 
  delay_ms(3000);

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