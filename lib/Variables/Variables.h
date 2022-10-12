#ifndef __VARIABLES_H
#define __VARIABLES_H
#include <Preferences.h>
#include <map>
#include <Arduino.h>
#include <AS608_Fingerprint.h>
#include <SoftwareSerial.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
using namespace std;
#define PLATFORM_FINGER Finger
#define PLATFORM_SERIAL Serial

typedef struct
{
    uint8_t Tx;                // Tx����
    uint8_t Rx;                // Rx����
    uint32_t Password;         //ָ��ģ������
    uint32_t SoftwareBaudrate; //���ڲ�����
    uint8_t Baudrate;          //ָ��ģ�鲨����
    uint16_t PacketSize;       //ָ��ģ�����С
    uint8_t SecurityLevel;     //ָ��ģ�鰲ȫ�ȼ�
} FingerPrint_Param;

typedef struct
{
    uint32_t Baudrate; //���ڲ�����
} Serial_Param;

extern DynamicJsonDocument finger_data;
extern FingerPrint_Param fingerprint_param;
extern HardwareSerial mySerial;
extern AS608_Fingerprint Finger;
extern Serial_Param serial_param;
extern File finger_file;
extern File system_log_file;

#endif /*__VARIABLES_H*/