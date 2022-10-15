#include <Libraries.h>



#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
AsyncWebServer server(80);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  LCD_setup(); //��ʼ��LCD

  show_first(); //��������
  delay(500);
  Store_Init();          //��ʼ���洢
  unclock_servo_setup(); //��ʼ�����
  setup_wifi();          //��ʼ��wifi
  FingerPrint_Init();    //��ʼ��ָ��ģ��
  Task_int();            //��ʼ�����߳�
  //������ IO0 ��ť������˵�
  pinMode(0, INPUT);
  attachInterrupt(0, show_menu, FALLING); // �����ⲿ�ж�
  //������ָ��ָ�ƴ������ϣ�׼��ָ��ʶ��
  pinMode(18, INPUT_PULLDOWN);
  attachInterrupt(18, FingerPrint_Unlock, RISING); // �����ⲿ�ж�

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Hi! This is a EN Door Web Page. V5.0.6"); });
  AsyncElegantOTA.begin(&server); // Start AsyncElegantOTA
  server.begin();

  //int_bt_Serial();  // ������������
  back_home_page(); //������ɣ���������
}

void loop()
{
  // LCD_while();
  // keypad_while();
  // put your main code here, to run repeatedly:
}
