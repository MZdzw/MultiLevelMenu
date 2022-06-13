#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "Menu.h"

int main(void)
{
  DDRB = 0x01;
  PORTB = 0b00000111;
  init();
  //inicjalizacja_struktury();
  //buf_str("Marcin");
  //lcd_refresh();
  //_delay_ms(1000);
  buf_clear();
  buf_send_number(0);
  while(1)
  {


      lcd_refresh();
  }
}
