#include <Libraries.h>

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

  xTaskCreate(
      keypad_Task,   /* Task function. */
      "keypad_Task", /* String with name of task. */
      10000,         /* Stack size in bytes. */
      NULL,          /* Parameter passed as input of the task */
      1,             /* Priority of the task. */
      NULL);         /* Task handle. */

  xTaskCreate(
      LCD_Task,   /* Task function. */
      "LCD_Task", /* String with name of task. */
      10000,      /* Stack size in bytes. */
      NULL,       /* Parameter passed as input of the task */
      1,          /* Priority of the task. */
      NULL);      /* Task handle. */

  //������ IO0 ��ť������˵�
  pinMode(0, INPUT);
  attachInterrupt(0, show_menu, FALLING); // �����ⲿ�ж�
}

void loop()
{
  // put your main code here, to run repeatedly:
}
