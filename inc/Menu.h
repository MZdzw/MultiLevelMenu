#define NULL 0

typedef struct Menu_struct menu_t;

struct Menu_struct
{
  char* name;
  menu_t* next;
  menu_t* prev;
  menu_t* child;
  menu_t* parent;
};

menu_t menu1, menu2, menu3, menu4, menu5, menu6;
menu_t submenu_2_1,submenu_2_2, submenu_2_3;
menu_t* current_pointer;
uint8_t menu_index;
uint8_t lcd_row_pos;

//OBSLUGA MENU
void inicjalizacja_struktury();
void menu_next(void);
void menu_refresh();
void menu_enter(void);
