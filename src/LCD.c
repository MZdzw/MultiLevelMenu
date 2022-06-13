#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"


void command(uint8_t bytes)
{
  send(bytes, 0);
}

void data(uint8_t bytes)
{
  send(bytes, 1);
}

void send(uint8_t bytes, uint8_t mode)
{
  if(!mode)
  {
    LCD_PORT = LCD_PORT & ~(1 << RS);
  }
  else
  {
    LCD_PORT = LCD_PORT | (1 << RS);
  }
  set_by(bytes >> 2);
  //
  set_by(bytes << 2);
}

void set_by(uint8_t bytes)
{
  LCD_PORT = (bytes & 0x3C) | (LCD_PORT & 0x03);
  LCD_PORT = LCD_PORT | (1 << EN);
  //_delay_us(1);
  LCD_PORT = LCD_PORT & ~(1 << EN);
  _delay_ms(0.3);
}

void set_by2(uint8_t bytes)
{
  LCD_PORT = (bytes & 0x3C) | (LCD_PORT & 0x03);
  LCD_PORT = LCD_PORT | (1 << EN);
  //_delay_us(1);
  LCD_PORT = LCD_PORT & ~(1 << EN);
}

void init()
{
  LCD_DDR = 0xFF;
  _delay_ms(16);
  LCD_PORT = LCD_PORT & ~(1 << EN) & ~(1 << RS);
  _delay_ms(4.1);
  command(0x03);
  _delay_ms(4.1);
  command(0x03);
  _delay_ms(4.1);
  command(0x03);
  _delay_ms(4.1);

  command(0x33);  //It's 4 bit initialization this and next
  _delay_ms(2);
  command(0x32);
  _delay_ms(2);
  command(FOUR_BIT_MODE);
  _delay_ms(2);
  command(CLEAR_DISPLAY);
  _delay_ms(2);
  command(RETURN_HOME);
  _delay_ms(1.52);
  command(TURN_ON_CURSOR);
  _delay_us(200);
  command(CURSOR_POSITION);
  _delay_us(200);
}

void set_cursor_position(uint8_t x, uint8_t y)
{
  uint8_t pos[] = {0x00, 0x40, 0x14, 0x54};
  if(x < 0 || x > COLUMNES)
    x = 0;
  if(y < 0 || y > ROWS)
    y = 0;
  command(CURSOR_POSITION + pos[y] + x);
}

void send_text(char* text)
{
  while(*text)
    data(*text++);
}

void buf_locate(uint8_t x, uint8_t y)
{
  lcd_buf_x = x;
  lcd_buf_y = y;
}

void buf_char(char c)
{
	if (lcd_buf_x < COLUMNES && lcd_buf_y < ROWS)
	{
		lcd_buf[lcd_buf_y][lcd_buf_x] = c;
		lcd_buf_x++;
		if (lcd_buf_x == COLUMNES)
    {
			lcd_buf_x = 0;
			lcd_buf_y++;
			if (lcd_buf_y == ROWS)
				lcd_buf_y = 0;
		}
	}
}

void buf_clear(void)
{
	for(uint8_t y = 0;  y < ROWS; y++)
	{
		for(uint8_t x = 0; x < COLUMNES; x++)
		{
			lcd_buf[y][x] = ' ';
		}
	}
	lcd_buf_x = 0; lcd_buf_y = 0;
}

void buf_str(char *text)
{
	while(*text)
		buf_char(*text++);
}

void lcd_refresh(void)
{
	static uint8_t locate_flag = 0; // informuje o konieczności przestawienia kursora lcd

	for(uint8_t y = 0; y < ROWS; y++)
	{
		//set_cursor_position( 0, y );    ////

		for(uint8_t x =0 ; x < COLUMNES; x++)
		{

			if( lcd_buf[y][x] != lcd_buf_old[y][x] )
			{
				if( !locate_flag )
				   set_cursor_position( x, y );   /////
        LCD_PORT = LCD_PORT | (1 << RS);  //RS na wysoki (data)
        //set_by2(lcd_buf[y][x] >> 2);     //wysylanie pierwsza polowka
			  data( lcd_buf[y][x] );
				lcd_buf_old[y][x] = lcd_buf[y][x];
				locate_flag = 1;
        //set_by2(lcd_buf[y][x] << 2);   //wysylanie druga polowka
			}
			else
				locate_flag = 0;
		}
	}
}

void buf_send_number(uint8_t number)
{
  char znaki[4] = {'i', 'i', 'i', '\0'};
  uint8_t i = 2;
  while(number != 0)
  {
    if(number % 10 == 0)
      znaki[i] = '0';
    else if(number % 10 == 1)
      znaki[i] = '1';
    else if(number % 10 == 2)
      znaki[i] = '2';
    else if(number % 10 == 3)
      znaki[i] = '3';
    else if(number % 10 == 4)
      znaki[i] = '4';
    else if(number % 10 == 5)
      znaki[i] = '5';
    else if(number % 10 == 6)
      znaki[i] = '6';
    else if(number % 10 == 7)
      znaki[i] = '7';
    else if(number % 10 == 8)
      znaki[i] = '8';
    else if(number % 10 == 9)
      znaki[i] = '9';

    i--;
    number = number/10;
  }
  if(znaki[2] == 'i')
    znaki[2] = '0';

  char *ptr = znaki;
  while(*ptr == 'i')
    ptr += 1;
  buf_str(ptr);
}
