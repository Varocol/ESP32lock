#include <Arduino.h>
#include <Serial_LCD.h>
#include <LCD_keypad.h>
#include <Unclock_Servo.h>

void keypad_Task(void *parameter)
{
  Serial.println("[�̹߳���]:��������ɨ���߳�");
  while (1)
  {
    keypad_while();
    delay(1);
  }
}

void LCD_Task(void *parameter)
{
  Serial.println("[�̹߳���]:��ĻͨѶ�߳�");
  while (1)
  {
    LCD_while();
    delay(1);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  LCD_setup();
  unclock_servo_setup();

  //������ IO0 ��ť������˵�
  pinMode(0, INPUT);
  attachInterrupt(0, show_menu, FALLING); // �����ⲿ�ж�
}

void loop()
{
  LCD_while();
  keypad_while();
  // put your main code here, to run repeatedly:
}
