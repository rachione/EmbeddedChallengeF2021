#include "myUI.h"

void LCDUI::Init()
{
    BSP_LCD_SetFont(&Font20);
    lcd.Clear(LCD_COLOR_BLACK);
}

void LCDUI::PageMenu()
{
    lcd.Clear(LCD_COLOR_BLACK);
    lcd.SetTextColor(LCD_COLOR_BLUE);
    lcd.FillRect(10, 65, 220, 50);
    lcd.FillRect(10, 185, 220, 50);

    lcd.SetBackColor(LCD_COLOR_BLUE);
    lcd.SetTextColor(LCD_COLOR_WHITE);

    lcd.DisplayStringAt(0, LINE(4), (uint8_t *)"Record", CENTER_MODE);
    lcd.DisplayStringAt(0, LINE(10), (uint8_t *)"Result", CENTER_MODE);
}

void LCDUI::PageRecord()
{
    BSP_LCD_SetFont(&Font12);
    lcd.Clear(LCD_COLOR_BLACK);
    lineCount = 0;
}
void LCDUI::PageResult()
{
    BSP_LCD_SetFont(&Font12);
    lcd.Clear(LCD_COLOR_BLACK);
    lineCount = 0;
}


/**
* @brief  Countdown for some seconds
* @param  sec: second.
* @retval None
*/
void LCDUI::PageCountDown(int sec)
{
    
    char str[32];
    for(int i=sec;i>=1;i--){
        sprintf(str, "Countdown %d!", i);
        lcd.Clear(LCD_COLOR_BLACK);
        lineCount = 0;
        Display(str);
        wait_us(1000 * 1000);
    }
    
}

/**
* @brief  Display Velocity on the LCD line by line.
* @param  str: Velocity.
* @retval None
*/
void LCDUI::DisplayVel(float *vel)
{
    char str[32];

    printf("X:%f Y:%f Z:%f\n", vel[0], vel[1], vel[2]);
    sprintf(str, "X:%.2f Y:%.2f Z:%.2f", vel[0], vel[1], vel[2]);
    Display(str);
}
/**
* @brief  Display on the LCD line by line.
* @param  str: display string.
* @retval None
*/
void LCDUI::Display(const char *str)
{
    if (lineCount > maxLine)
    {
        lineCount = 0;
        lcd.Clear(LCD_COLOR_BLACK);
    }
    
    lcd.SetBackColor(LCD_COLOR_BLACK);
    lcd.SetTextColor(LCD_COLOR_WHITE);
    lcd.DisplayStringAt(0, LINE(lineCount++), (uint8_t *)str, LEFT_MODE);
}
