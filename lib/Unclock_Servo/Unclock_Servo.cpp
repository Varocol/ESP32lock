#include "Unclock_Servo.h"

#define open_angle 80             //�����Ƕ�
#define close_angle 0             //�����Ƕ�
#define servo_pin 21              //���ö������21
#define servo_freq 50             //�̶�50Hz
#define servo_max_pulse_with 2500 //����������(us)
#define servo_min_pulse_with 500  //�����С����(us)
Servo unclock_servo;

void unclock_servo_setup()
{
    // ESP32PWM::allocateTimer(0);
    // unclock_servo.attach(servo_pin, 1000, 2000);
    pwm_setup();
}

void pwm_setup()
{
    pinMode(servo_pin, OUTPUT);
}

void pwm_generate(int angle, int ms)
{
    int cycle = ms > 20 ? ms / 20 : 1;
    uint32_t time = angle / 180.0 * (servo_max_pulse_with - servo_min_pulse_with) + servo_min_pulse_with;
    Serial.printf("time = %d\ncycle = %d\n", time, cycle);
    while (cycle--)
    {
        digitalWrite(servo_pin, HIGH);
        delayMicroseconds(time);
        digitalWrite(servo_pin, LOW);
        delayMicroseconds(20000 - time);
    }
}

void open_Task(void *parameter)
{
    Serial.println("[Ӳ������]: ����");
    // unclock_servo.setPeriodHertz(50); // ����Ƶ��Ϊ50Hz
    pwm_generate(open_angle, 1000);
    Serial.println("[Ӳ������]: ����");
    pwm_generate(close_angle, 1000);
    // unclock_servo.setPeriodHertz(0); // �ر�Ƶ�ʣ���ֹ�ն��
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