#include "mqtt.h"
#include "WiFiClient.h"
#include <PubSubClient.h>
#include "ArduinoJson.h"
#include <Preferences.h>
#include "WiFi.h"

// MQTT Broker
const char *mqtt_broker = "broker-cn.emqx.io"; //��������ַ
const int mqtt_port = 1883;                    //�˿ں�
const char *mqtt_username = "emqx";            //�û���
const char *mqtt_password = "public";          //����
const char *rec_topic = "ENdoor/rec";          //��������
const char *send_topic = "ENdoor/send";        //��������
const char *clientID = "ESP32-20501";          //�ͻ���ID

WiFiClient espClient;
PubSubClient client(espClient);

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    String raw_data;
    for (int i = 0; i < length; i++)
    {
        raw_data += (char)payload[i];
    }
    // Serial.println("[�������]:�յ�������:" + raw_data);
    DynamicJsonDocument doc(2048);
    if (deserializeJson(doc, raw_data))
    {
        Serial.println("[�������]:MQTT�յ��˷�JSON����:" + raw_data);
        return;
    }
    //�ȹ�һ�¹���Ա��֤
    Preferences prefs;                                           // ����Preferences����
    prefs.begin("config");                                       // �������ռ�config
    String real_admin_password = prefs.getString("admin_k", ""); // ��ȡ����Ա����
    prefs.end();
    String key = doc["key"].as<String>();
    if (key != real_admin_password)
    {
        Serial.println("[�������]:MQTT����������֤����:" + key);
        mqtt_show_tips("����", "�������");
        return;
    }

    String type = doc["type"].as<String>();

    if (type == "set_admin_passwd")
    {
        // ���ù���Ա����
        String new_passwd = doc["passwd"].as<String>();

        if (new_passwd.length() != 6)
        {
            // ���Ȳ���
            mqtt_show_tips("��������ʧ��", "��������ǳ���6λ");
            return;
        }
        Preferences prefs;                                         // ����Preferences����
        prefs.begin("config");                                     // �������ռ�config
        String real_user_password = prefs.getString("user_k", ""); // ��ȡ�û�����
        if (new_passwd == real_user_password)
        {
            // �������ͨ�û�������ͬ
            mqtt_show_tips("��������ʧ��", "����Ա���벻�ܺ���ͨ������ͬ");
            return;
        }
        prefs.putString("admin_k", new_passwd); // д���������
        prefs.end();                            // �ر������ռ�
                                                // ���óɹ�
        Serial.println("[�������]:�޸Ĺ���Ա����Ϊ:" + new_passwd);
        mqtt_show_tips("�޸ĳɹ�", "����Ա�������޸�");
        return;
    }
    if (type == "set_user_passwd")
    {
        // �����û�����
        String new_passwd = doc["passwd"].as<String>();

        if (new_passwd.length() != 6)
        {
            // ���Ȳ���
            mqtt_show_tips("��������ʧ��", "��������ǳ���6λ");
            return;
        }
        Preferences prefs;                                          // ����Preferences����
        prefs.begin("config");                                      // �������ռ�config
        String real_user_password = prefs.getString("admin_k", ""); // ��ȡ�û�����
        if (new_passwd == real_user_password)
        {
            // �������ͨ�û�������ͬ
            mqtt_show_tips("��������ʧ��", "��ͨ���벻�ܺ͹���Ա������ͬ");
            return;
        }
        prefs.putString("user_k", new_passwd); // д���������
        prefs.end();                           // �ر������ռ�
                                               // ���óɹ�
        Serial.println("[�������]:�޸���ͨ����Ϊ:" + new_passwd);
        mqtt_show_tips("�޸ĳɹ�", "��ͨ�������޸�");
        return;
    }
    if (type == "check")
    {
        mqtt_check_online();
        return;
    }
}

// MQTT������ҳ������ʾ��
void mqtt_show_tips(String title, String center)
{
    DynamicJsonDocument doc(2048);
    doc["type"] = "tips";
    doc["title"] = title;
    doc["center"] = center;
    String json;
    serializeJson(doc, json);
    client.publish(send_topic, json.c_str());
}
// �����豸���
void mqtt_check_online()
{
    DynamicJsonDocument doc(2048);
    doc["type"] = "online";
    doc["MAC"] = String(WiFi.macAddress());
    doc["IP"] = WiFi.localIP().toString();
    String json;
    serializeJson(doc, json);
    client.publish(send_topic, json.c_str());
}

void mqtt_int()
{
    client.disconnect();
    client.setServer(mqtt_broker, mqtt_port);
    client.connect(clientID, mqtt_username, mqtt_password);
    client.setCallback(&mqtt_callback);
    client.subscribe(rec_topic);
    mqtt_check_online();
    Serial.println("[�������]:mqtt���ӳɹ�");
}

void mqtt_disable()
{
    client.disconnect();
}

void mqtt_while()
{
    client.loop();
}