#ifndef __Serial_LCD_h
#define __Serial_LCD_h

#include <Arduino.h>
#include <vector>

using namespace std;

// �����ຯ��
void LCD_setup();
void LCD_print(String out_data);
void LCD_while();
void deal_lcd_cmd(String raw_data);
void LCD_debug(String str);
void keypad_while();

// �����ຯ��
void show_confirm(String title, String center, String last_page, String cmd);
void show_tips(String title, String center, String last_page);
void back_home_page();
void show_menu();

#endif // __Serial_LCD_h