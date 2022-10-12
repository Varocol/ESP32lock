#include <network_config.h>
#include <WiFi.h>
#include <Preferences.h>
#include <task.h>
#include <Serial_LCD.h>
#include "mqtt.h"

wl_status_t last_network_state = WL_IDLE_STATUS;

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

void network_config_Task(void *parameter)
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
    show_tips("�����ɹ���������", WiFi.SSID() + "\\r����: " + WiFi.psk(), "0"); // ��ʾ��ʾ
    delay(30000);
    ESP.restart();
}

void network_config_begin()
{
    xTaskCreate(
        network_config_Task,   /* Task function. */
        "network_config_Task", /* String with name of task. */
        10000,                 /* Stack size in bytes. */
        NULL,                  /* Parameter passed as input of the task */
        1,                     /* Priority of the task. */
        NULL);                 /* Task handle. */
    Task_Die();                // �Ȱ������߳�ȫ������
}

void Network_while()
{
    if (WiFi.status() != last_network_state)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            // �����ɹ��ص�
            Serial.print("[�������]:�����ɹ���IP:");
            Serial.println(WiFi.localIP());
            configTime(60*60*8, 0, "ntp3.aliyun.com");    // �õİ����Ƶķ�����
            // ��Ȼ�Ѿ������ɹ��ˣ���Ϊʲô������ MQTT ��
            mqtt_int();
        }
        else
        {
            // ����Ͽ��ص�
            Serial.println("[�������]:����Ͽ�");
            mqtt_disable();
        }
    }
    last_network_state = WiFi.status();
    if (WiFi.status() == WL_CONNECTED)
    {
        mqtt_while();
    }
}
