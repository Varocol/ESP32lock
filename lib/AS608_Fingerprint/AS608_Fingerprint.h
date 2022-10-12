#ifndef __AS608_FINGERPRINT_H
#define __AS608_FINGERPRINT_H
#include <Adafruit_Fingerprint.h>
#include <vector>
#include <SoftwareSerial.h>
using namespace std;

//AS608����ָ��
#define FINGERPRINT_WRITENOTEPAD 0x18
#define FINGERPRINT_READNOTEPAD 0x19
#define FINGERPRINT_AUTOENROLL 0x10
#define FINGERPRINT_AUTOIDENTIFY 0x11
#define FINGERPRINT_READINDEXTABLE 0x1F

//AS60״̬��
#define FINGERPRINT_UNKOWNERR 0x19
#define FINGERPRINT_REGCONTENTERR 0x1B
#define FINGERPRINT_PAGERANGEERR 0x1C
#define FINGERPRINT_COMOPERATEERR 0x1D
#define FINGERPRINT_AUTOENROLLERR 0x1E
#define FINGERPRINT_DBFULL 0x1F

//�����Զ�¼�롢�Զ���֤�����±��Լ���ȡ��������
class AS608_Fingerprint : public Adafruit_Fingerprint
{
private:
public:
#if defined(__AVR__) || defined(ESP32) || defined(ESP8266) || defined(FREEDOM_E300_HIFIVE1)
    AS608_Fingerprint(SoftwareSerial *ss, uint32_t password = 0x0);
#endif
    AS608_Fingerprint(HardwareSerial *hs, uint32_t password = 0x0);
    AS608_Fingerprint(Stream *serial, uint32_t password = 0x0);
    uint8_t autoEnroll();
    uint8_t autoIdentify();
    uint8_t readIndexTable();
    uint8_t writeNotepad(uint8_t pagenum, uint8_t *pagedataptr);
    uint8_t readNotepad(uint8_t pagenum,uint8_t *pagedataptr);
    vector<uint16_t>IndexTable;
    uint16_t autoEnrollindex;
    
};

#endif /*__AS608_FINGERPRINT_H*/