#include "Unclock_Servo.h"

#define open_angle 80 //�����Ƕ�
#define close_angle 0 //�����Ƕ�
#define servo_pin 21  //���ö������21

Servo unclock_servo;

void unclock_servo_setup()
{
    ESP32PWM::allocateTimer(3);
    unclock_servo.attach(servo_pin, 1000, 2000);
    unclock_servo.setPeriodHertz(50); // ����Ƶ��Ϊ50Hz
}

void open_Task(void *parameter)
{
    Serial.println("[Ӳ������]: ����");
    for (int i = close_angle; i < open_angle; i++)
    {
        unclock_servo.write(i);
        delay(10);
    }
    delay(1000);
    Serial.println("[Ӳ������]: ����");
    for (int i = open_angle; i > close_angle; i--)
    {
        unclock_servo.write(i);
        delay(10);
    }
    delay(1000);
    vTaskDelete(NULL);
}

void unclock_servo_open()
{
    xTaskCreate(
        open_Task,   /* Task function. */
        "open_Task", /* String with name of task. */
        10000,       /* Stack size in bytes. */
        NULL,        /* Parameter passed as input of the task */
        1,           /* Priority of the task. */
        NULL);       /* Task handle. */
}