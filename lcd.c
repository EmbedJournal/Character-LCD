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
    Delay10KTCYx(200);                     // wait for 20 ms
    lcd_init_cmd();
    LCD_cmd(MODE_4BIT);
    LCD_cmd(CLRSCR);                      // clear the screen
    LCD_cmd(CURSOR_INC);                  // Cursor Incremetns on each write
    LCD_cmd(DISPLAY_ON | CURSOR_OFF);     // Display on and Cursor Off
}	

void LCD_data(unsigned char data)
{
    unsigned char upperNibble;
    unsigned char lowerNibble;
    LCD_isbusy();
    RS = HIGH;
    upperNibble = data >> 4;
    lowerNibble = data & 0x0f;
    LCD_write_nibble(upperNibble);
    LCD_write_nibble(lowerNibble);
}

void LCD_cmd(unsigned char cmd)
{
    unsigned char upperNibble;
    unsigned char lowerNibble;
    LCD_isbusy();
    RS = LOW;
    upperNibble = cmd >> 4;
    lowerNibble = cmd & 0x0f;
    LCD_write_nibble(upperNibble);
    LCD_write_nibble(lowerNibble);
}

void LCD_write_nibble(unsigned char nibble)
{
    EN = HIGH;
    RW = LOW;
    DATAPORT |= nibble;
    Delay10KTCYx(100);
    EN = LOW;
}

unsigned char LCD_read_nibble(void)
{
    unsigned char nibble;
    TRISB |= 0x0F;
    EN = HIGH;
    RS = LOW;
    RW = HIGH;
    nibble = DATAPORT & 0x0F;
    Delay10KTCYx(100);
    EN = LOW;
    TRISB = 0x00;
    return nibble;
}

void LCD_isbusy(void)
{
    unsigned char upperNibble;
    unsigned char lowerNibble;
    do
    {
    upperNibble = LCD_read_nibble();
    lowerNibble = LCD_read_nibble();
    }while (!(upperNibble & 0x08));
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

void LCD_blink(void)
{
    LCD_cmd(DISPLAY_OFF);
    Delay10KTCYx(255);
    Delay10KTCYx(255);
    LCD_cmd(DISPLAY_ON);
    Delay10KTCYx(255);
    Delay10KTCYx(255);
    LCD_cmd(DISPLAY_OFF);
    Delay10KTCYx(255);
    Delay10KTCYx(255);
    LCD_cmd(DISPLAY_ON);
    Delay10KTCYx(255);
    Delay10KTCYx(255);
}

void lcd_init_cmd(void)
{
    RS = LOW;
    RW = LOW;
    LCD_write_nibble(0x03);
    Delay10KTCYx(255);
    LCD_write_nibble(0x03);
    Delay10KTCYx(255);
    LCD_write_nibble(0x03);
    Delay10KTCYx(255);
    LCD_write_nibble(0x02);
    Delay10KTCYx(255);
}
