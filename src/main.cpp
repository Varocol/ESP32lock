#include <Libraries.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  LCD_setup();
  unclock_servo_setup();
  setup_wifi();

  Task_int();
  //������ IO0 ��ť������˵�
  pinMode(0, INPUT);
  attachInterrupt(0, show_menu, FALLING); // �����ⲿ�ж�
}

void loop()
{
  // LCD_while();
  // keypad_while();
  // put your main code here, to run repeatedly:
}
