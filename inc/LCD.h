#define LCD_DDR DDRD
#define LCD_PORT PORTD
#define EN PD1
#define RS PD0

#define FOUR_BIT_MODE 0x28
#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02
#define TURN_ON_CURSOR 0x0E
#define SCROLL_DIPLAY_RIGHT 0x1E
#define SCROLL_DIPLAY_LEFT 0x18
#define CURSOR_POSITION 0x80

#define ROWS 2
#define COLUMNES 16


char lcd_buf_old[ROWS][COLUMNES];
char lcd_buf[ROWS][COLUMNES];
uint8_t lcd_buf_x, lcd_buf_y;




//NAWIGACJA PO MENU

//////

//FUNKCJE OBSLUGUJACE WYSWIETLACZ
void command(uint8_t bytes);
void data(uint8_t bytes);
void send(uint8_t bytes, uint8_t mode);
void set_by(uint8_t bytes);
void set_by2(uint8_t bytes);
void init();
void set_cursor_position(uint8_t x, uint8_t y);
void send_text(char *text);
///////////////////////

//BUFOR WYSWIETLACZA
void buf_locate(uint8_t x, uint8_t y);
void buf_char(char c);
void buf_clear(void);
void buf_str(char *text);
void lcd_refresh(void);
void buf_send_number(uint8_t number);
/////////////////////////
