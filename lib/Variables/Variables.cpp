#include <Variables.h>
//ָ��ģ�������
/*
json��ʽ
{
    "1":{
        "school_id":
        "operations_cnt":
    },
    "2":{
        ...
    },
    ...
}
*/
//Ԥ����2k�ռ�
DynamicJsonDocument finger_data(2048);
FingerPrint_Param fingerprint_param = {
    .Tx = 16,
    .Rx = 17,
    .Password = 0,
    .SoftwareBaudrate = 9600,
    .Baudrate = FINGERPRINT_BAUDRATE_9600,
    .PacketSize = FINGERPRINT_PACKET_SIZE_256,
    .SecurityLevel = FINGERPRINT_SECURITY_LEVEL_1};
HardwareSerial mySerial(2);
AS608_Fingerprint Finger(&mySerial);

//���ڱ�����
Serial_Param serial_param = {
    .Baudrate = 115200};

//�ļ�ϵͳ����
File finger_file;
File system_log_file;