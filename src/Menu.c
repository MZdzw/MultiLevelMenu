#include <avr/io.h>
#include "Menu.h"
#include "LCD.h"


void inicjalizacja_struktury()
{
  menu1.name = "MENU GLOWNE";
  menu1.next = &menu2;
  menu1.prev = &menu6;
  menu1.parent = NULL;
  menu1.child = NULL;

  menu2.name = "ELEMENT 2";
  menu2.next = &menu3;
  menu2.prev = &menu1;
  menu2.parent = NULL;
  menu2.child = &submenu_2_1;

  menu3.name = "INNY";
  menu3.next = &menu4;
  menu3.prev = &menu2;
  menu3.parent = NULL;
  menu3.child = NULL;

  menu4.name = "ELEMENT 4";
  menu4.next = &menu5;
  menu4.prev = &menu3;
  menu4.parent = NULL;
  menu4.child = NULL;

  menu5.name = "ELEMENT 5";
  menu5.next = &menu6;
  menu5.prev = &menu4;
  menu5.parent = NULL;
  menu5.child = NULL;

  menu6.name = "ELEMENT 6";
  menu6.next = NULL;
  menu6.prev = &menu5;
  menu6.parent = NULL;
  menu6.child = NULL;

  submenu_2_1.name = "ELEMENT 2_1";
  submenu_2_1.next = &submenu_2_2;
  submenu_2_1.prev = &submenu_2_3;
  submenu_2_1.parent = &menu2;
  submenu_2_1.child = NULL;

  submenu_2_2.name = "ELEMENT 2_2";
  submenu_2_2.next = &submenu_2_3;
  submenu_2_2.prev = &submenu_2_1;
  submenu_2_2.parent = &menu2;
  submenu_2_2.child = NULL;

  submenu_2_3.name = "ELEMENT 2_3";
  submenu_2_3.next = NULL;
  submenu_2_3.prev = &submenu_2_2;
  submenu_2_3.parent = &menu2;
  submenu_2_3.child = NULL;

  current_pointer = &menu1;
  menu_index = 0;
  lcd_row_pos = 0;
}

void menu_next(void)
{
  if(current_pointer->next)   //jezeli istnieje nastepny element listy
  {
    current_pointer = current_pointer->next;
    menu_index++;
    if(++lcd_row_pos > ROWS - 1)
      lcd_row_pos = ROWS - 1;
  }
  else
  {
    menu_index = 0;
    lcd_row_pos = 0;

    if(current_pointer->parent)
      current_pointer = (current_pointer->parent)->child;
    else
      current_pointer = &menu1;
  }
  menu_refresh();
}

void menu_refresh(void)
{
  menu_t *temp;
	uint8_t i;

	if (current_pointer->parent) temp = (current_pointer->parent)->child;
	else temp = &menu1;

	for (i = 0; i != menu_index - lcd_row_pos; i++) {
		temp = temp->next;
	}

	buf_clear();
	for (i = 0; i < ROWS; i++)
  {
		buf_locate(0, i);
		if (temp == current_pointer) buf_char(62);
		else buf_char(' ');
		buf_locate(2, i);
		buf_str(temp->name);

		temp = temp->next;
		if (!temp) break;

	}
	// lcd_refresh();
}

void menu_enter(void)
{
	if (current_pointer->child)
	{
		/*switch (menu_get_level(current_pointer)) {
			case 0:
				lcd_row_pos_level_1 = lcd_row_pos;
				break;

			case 1:
				lcd_row_pos_level_2 = lcd_row_pos;
				break;
		} */

		// switch...case can be replaced by:
		// lcd_row_pos_level[ menu_get_level(currentPointer) ] = lcd_row_pos;

		menu_index = 0;
		lcd_row_pos = 0;

		current_pointer = current_pointer->child;

		menu_refresh();
	}
}

uint8_t menu_get_level(menu_t *q)
{
	menu_t *temp = q;
	uint8_t i = 0;

	if (!q->parent) return 0;

	while (temp->parent != NULL) {
		temp = temp->parent;
		i++;
	}

	return i;
}
