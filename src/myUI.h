

#include <mbed.h>
#include <string.h>
#include "LCD_DISCO_F429ZI.h"

class LCDUI
{
private:
    const int maxLine = 25;
    int lineCount = 0;
    LCD_DISCO_F429ZI lcd;

public:
    void Init();
    void PageMenu();
    void PageRecord();
    void PageResult();
    void DisplayVel(float *vel);
    void Display(const char *str);
};
