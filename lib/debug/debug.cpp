#include <debug.h>
#include "HardwareSerial.h"
#include <Serial_LCD.h>
#include <Variables.h>
#include <task.h>

extern HardwareSerial LCD_Serial;
extern HardwareSerial mySerial;

void debug_LCD_Task(void *parameter)
{
    Serial.println("[����]:��ʼ������Ļ��ת����Ļ����");
    LCD_print("page 8");
    LCD_print("backtim.en=0");
    LCD_print("t0.txt=\"������Ļ��\"");
    while (1)
    {
        if (Serial.available() > 0)
        {
            LCD_Serial.write(Serial.read());
        }
        if (LCD_Serial.available() > 0)
        {
            Serial.write(LCD_Serial.read());
        }
        delay(1);
    }
}

void debug_finger_Task(void *parameter)
{
    Serial.println("[����]:��ʼ����ָ��ģ�飬ת��ָ��ģ������");
    LCD_print("page 8");
    LCD_print("backtim.en=0");
    LCD_print("t0.txt=\"����ָ��ģ����\"");
    while (1)
    {
        if (Serial.available() > 0)
        {
            mySerial.write(Serial.read());
        }
        if (mySerial.available() > 0)
        {
            Serial.write(mySerial.read());
        }
        delay(1);
    }
}

void debug_LCD()
{
    xTaskCreate(
        debug_LCD_Task,   /* Task function. */
        "debug_LCD_Task", /* String with name of task. */
        10000,            /* Stack size in bytes. */
        NULL,             /* Parameter passed as input of the task */
        1,                /* Priority of the task. */
        NULL);            /* Task handle. */
    Task_Die();
}

void debug_finger()
{
    xTaskCreate(
        debug_finger_Task,   /* Task function. */
        "debug_finger_Task", /* String with name of task. */
        10000,               /* Stack size in bytes. */
        NULL,                /* Parameter passed as input of the task */
        1,                   /* Priority of the task. */
        NULL);               /* Task handle. */
    Task_Die();
}