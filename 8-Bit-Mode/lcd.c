/*Copyright (c) 2014 EmbedJournal.

Author: Siddharth Chandrasekaran
Website: http://embedjournal.com/

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
#include<p18f4520.h>
#include<delays.h>
#include"lcd.h"

void LCD_init(void){
    TRISD=0x00;
    TRISB=0x00;
    LCD_cmd(MODE_8BIT);                   // 2 Line, 5x7 display, 8 bit
    LCD_cmd(CLRSCR);                      // clear the screen
    LCD_cmd(CURSOR_INC);                  // Cursor Incremetns on each write
    LCD_cmd(DISPLAY_ON | CURSOR_OFF);     // Display on and Cursor Off
    return;
}	

void LCD_data(unsigned char data){
    LCD_isbusy();
    RS = HIGH;
    RW = LOW;
    EN = HIGH;
    DATAPORT = data;
    Delay1KTCYx(50);
    EN = LOW;
}
	
void LCD_cmd(unsigned char cmd){
    LCD_isbusy();
    RS = LOW;
    RW = LOW;
    EN = HIGH;
    DATAPORT = cmd;
    Delay1KTCYx(50);
    EN = LOW;
}	
void LCD_string(const rom char *buffer)
{
    while(*buffer)              // Write data to LCD up to null
    {
        LCD_isbusy();           // Wait while LCD is busy
        LCD_data(*buffer);      // Write character to LCD
        buffer++;               // Increment buffer
    }
}
void LCD_isbusy(void)
{
    TRISBbits.TRISB7=1;         // Make D7 as input
    RS = LOW;
    RW = HIGH;
    EN = HIGH;
    Delay1KTCYx(50);
    while(BF);
    TRISBbits.TRISB7=0;         // Back to Output
    EN = LOW;
}
