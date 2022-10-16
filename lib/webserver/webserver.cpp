#include "webserver.h"
#include <Preferences.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
AsyncWebServer server(80);

void int_web()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hi! This is a EN Door Web Page. V5.0.6"); });

    server.on("/unlock", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                String back_data;
            if (request->hasParam("admin_key")) {
                String inputMessage1;
                inputMessage1 = request->getParam("admin_key")->value();
                //�����߼�
                Preferences prefs;                                           // ����Preferences����
                prefs.begin("config");                                       // �������ռ�config
                String real_admin_password = prefs.getString("admin_k", ""); // ��ȡ����Ա����
                prefs.end();
                if(inputMessage1 == real_admin_password){
                    back_data = "{\"e\":\"�����ɹ�\"}";
                }else{
                    back_data = "{\"e\":\"����Ա�������\"}";
                }
            }
            else {
                back_data = "{\"e\":\"���������Ա����\"}";
            }
            request->send(200, "application/json", back_data); });

    AsyncElegantOTA.begin(&server); // Start AsyncElegantOTA
    server.begin();
}