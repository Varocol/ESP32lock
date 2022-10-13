#include <task.h>
#include "LCD_keypad.h"
#include "Serial_LCD.h"
#include "network_config.h"

//�������
TaskHandle_t xHandle_keypad_Task = NULL;
TaskHandle_t xHandle_LCD_Task = NULL;
TaskHandle_t xHandle_Network_Task = NULL;

void Task_Die()
{
    if (xHandle_keypad_Task != NULL)
        vTaskDelete(xHandle_keypad_Task); // ɾ�������߳�
    if (xHandle_LCD_Task != NULL)
        vTaskDelete(xHandle_LCD_Task); // ɾ��LCD�߳�
    if (xHandle_Network_Task != NULL)
        vTaskDelete(xHandle_Network_Task); // ɾ�������߳�
}

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
    Serial.println("[�̹߳���]:������ĻͨѶ�߳�");
    while (1)
    {
        LCD_while();
        delay(1);
    }
}

void Network_Task(void *parameter)
{
    Serial.println("[�̹߳���]:���������߳�");
    while (1)
    {
        Network_while();
        delay(1);
    }
}



void Task_int()
{
    xTaskCreate(
        keypad_Task,           /* Task function. */
        "keypad_Task",         /* String with name of task. */
        10000,                 /* Stack size in bytes. */
        NULL,                  /* Parameter passed as input of the task */
        1,                     /* Priority of the task. */
        &xHandle_keypad_Task); /* Task handle. */

    xTaskCreate(
        LCD_Task,           /* Task function. */
        "LCD_Task",         /* String with name of task. */
        10000,              /* Stack size in bytes. */
        NULL,               /* Parameter passed as input of the task */
        1,                  /* Priority of the task. */
        &xHandle_LCD_Task); /* Task handle. */

    xTaskCreate(
        Network_Task,           /* Task function. */
        "Network_Task",         /* String with name of task. */
        10000,                  /* Stack size in bytes. */
        NULL,                   /* Parameter passed as input of the task */
        1,                      /* Priority of the task. */
        &xHandle_Network_Task); /* Task handle. */
}