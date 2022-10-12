#include "mqtt.h"
#include "WiFiClient.h"
#include <PubSubClient.h>

// MQTT Broker
const char *mqtt_broker = "broker-cn.emqx.io"; //��������ַ
const int mqtt_port = 1883;                    //�˿ں�
const char *mqtt_username = "emqx";            //�û���
const char *mqtt_password = "public";          //����
const char *topic = "ENdoor";                  //��������
const char *clientID = "ESP32";                //�ͻ���ID

WiFiClient espClient;
PubSubClient client(espClient);

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

void mqtt_int()
{
    client.disconnect();
    client.setServer(mqtt_broker, mqtt_port);
    client.connect(clientID, mqtt_username, mqtt_password);
    client.setCallback(&mqtt_callback);
    client.subscribe(topic);
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