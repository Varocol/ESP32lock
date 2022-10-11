#include <network_config.h>
#include <WiFi.h>
#include <Preferences.h>
#include <Serial_LCD.h>

void setup_wifi()
{
    Preferences prefs;     // ����Preferences����
    prefs.begin("config"); // �������ռ�config
    WiFi.mode(WIFI_AP_STA);
    String wifi_ssid = prefs.getString("ssid", "");     // ��ȡssid
    String wifi_passwd = prefs.getString("passwd", ""); // ��ȡpasswd
    if (wifi_ssid != "" && wifi_passwd != "")
    {
        WiFi.begin(wifi_ssid.c_str(), wifi_passwd.c_str());
        Serial.println("[�������]:WIFI���ӵ�:" + wifi_ssid);
    }
    else
    {
        Serial.println("[�������]:û�ж�ȡ��WIFI���ݣ�����������");
    }
    prefs.end(); // �ر������ռ�config
}

void network_config_begin()
{
    Serial.println("[�̹߳���]:����SmartConfig�����߳�");
    Preferences prefs;     // ����Preferences����
    prefs.begin("config"); // �������ռ�config
    WiFi.beginSmartConfig();
    // Wait for SmartConfig packet from mobile
    Serial.println("[�������]:�ȴ�SmartConfig����");
    while (!WiFi.smartConfigDone())
    {
        LCD_print("network.t0.txt=\"��\"");
        delay(500);
        LCD_print("network.t0.txt=\"|\"");
        delay(500);
    }
    prefs.putString("ssid", WiFi.SSID());  // д��ssid
    prefs.putString("passwd", WiFi.psk()); // д��passwd
    prefs.end();                           // �ر������ռ�config
    Serial.println("[�������]:������ɣ��ȴ�30������");
    LCD_print("tips.title.txt=\"�����ɹ���������\"");
    LCD_print("tips.center.txt=\"WIFI: " + WiFi.SSID() + "\r����: " + WiFi.psk() + "\"");
    LCD_print("tips.last_page.val=0");
    LCD_print("page tips");
    delay(30000);
    ESP.restart();
}