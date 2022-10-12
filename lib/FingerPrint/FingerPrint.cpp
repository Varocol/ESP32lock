#include <FINGERPrint.h>
#include <Variables.h>
#include <Serial_LCD.h>
/**
 * @author  @Varocol
 * @brief   ָ��ģ���ʼ��
 * @param   None
 * @return  None
 */
void FingerPrint_Init()
{
    PLATFORM_SERIAL.println("<-------------ָ��ģ���ʼ��------------->");
    //��������
    mySerial.begin(fingerprint_param.SoftwareBaudrate, SERIAL_8N1, fingerprint_param.Rx, fingerprint_param.Tx);
    //��֤����
    if (PLATFORM_FINGER.verifyPassword())
    {
        PLATFORM_SERIAL.println("[ָ��ģ��]:�ҵ�ָ��ʶ��ģ��");
        uint8_t status;
        uint8_t time_limit;
        // ���ð���С
        time_limit = FINGER_TIMELIMIT;
        while ((status = PLATFORM_FINGER.setPacketSize(fingerprint_param.PacketSize)) != FINGERPRINT_OK && time_limit != 0)
        {
            //״̬����
            PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
            //��ʱ100ms
            delay(100);
            time_limit--;
        }
        if (time_limit == 0)
        {
            PLATFORM_SERIAL.println("[ָ��ģ��]:ָ�����ݰ���С����ʧ��");
        }
        else
        {
            PLATFORM_SERIAL.println("[ָ��ģ��]:ָ�����ݰ���С���óɹ�");
        }
        //����ͨѶ����
        time_limit = FINGER_TIMELIMIT;
        while ((status = PLATFORM_FINGER.setBaudRate(fingerprint_param.Baudrate)) != FINGERPRINT_OK && time_limit != 0)
        {
            //״̬����
            PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
            //��ʱ100ms
            delay(100);
            time_limit--;
        }
        if (time_limit == 0)
        {
            PLATFORM_SERIAL.println("[ָ��ģ��]:ͨѶ��������ʧ��");
        }
        else
        {
            PLATFORM_SERIAL.println("[ָ��ģ��]:ͨѶ�������óɹ�");
        }
        //��ʱ����
        delay(100);
#if FINGER_SETPASSWORD
        //��������
        time_limit = FINGER_TIMELIMIT;
        while ((status = PLATFORM_FINGER.setPassword(fingerprint_param.Password)) != FINGERPRINT_OK && time_limit != 0)
        {
            //״̬����
            PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
            //��ʱ100ms
            delay(100);
            time_limit--;
        }
        if (time_limit == 0)
        {
            PLATFORM_SERIAL.println("[ָ��ģ��]:��������ʧ��");
        }
        else
        {
            PLATFORM_SERIAL.println("[ָ��ģ��]:�������óɹ�");
        }
#endif
        //���ð�ȫ�ȼ�
        time_limit = FINGER_TIMELIMIT;
        while ((status = PLATFORM_FINGER.setSecurityLevel(fingerprint_param.SecurityLevel)) != FINGERPRINT_OK && time_limit != 0)
        {
            //״̬����
            PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
            //��ʱ100ms
            delay(100);
            time_limit--;
        }
        if (time_limit == 0)
        {
            PLATFORM_SERIAL.println("[ָ��ģ��]:��ȫ�ȼ�����ʧ��");
        }
        else
        {
            PLATFORM_SERIAL.println("[ָ��ģ��]:��ȫ�ȼ����óɹ�");
        }
        //��ʾ���ú�Ĳ���
        FingerPrint_ShowParameters();
        //��ģ���л�ȡ���ڵ�ָ��������
        FingerPrint_GetIndexTable();
        //���ļ�ϵͳ����ָ����������ӳ�����Ϣ(ѧ�š���ѯ��Ϣ)
        FingerPrint_LoadList();
        PLATFORM_SERIAL.println("[ָ��ģ��]:ָ��ʶ��ģ���ʼ���ɹ�");
    }
    else
    {
        PLATFORM_SERIAL.println("[ָ��ģ��]:δ���ҵ�ָ��ʶ��ģ��");
        PLATFORM_SERIAL.println("[ָ��ģ��]:ָ��ʶ��ģ���ʼ��ʧ��");
    }
}

/**
 * @author  @Varocol
 * @brief   ��ȡģ�������ͨ��������ʾ
 * @param   None
 * @return  None
 */
void FingerPrint_ShowParameters()
{
    PLATFORM_SERIAL.println("[ָ��ģ��]:��ȡģ�����");
    //��ȡָ��ģ�����
    uint8_t time_limit = FINGER_TIMELIMIT;
    while (PLATFORM_FINGER.getParameters() != FINGERPRINT_OK && time_limit != 0)
    {
        time_limit--;
        //��ʱ100ms
        delay(100);
    }
    if (time_limit != 0)
    {
        PLATFORM_SERIAL.println("[ָ��ģ��]:�������ͨ��");
        PLATFORM_SERIAL.printf(
            "-----------ָ��ģ�����----------\n"
            "״̬:%s\n"
            "ID:%d\n"
            "����:%d\n"
            "ʶ��ȼ�(1~5):%d\n"
            "�豸��ַ:%#x\n"
            "���ݰ���С:%d\n"
            "������:%d\n"
            "--------------------------------\n",
            FingerPrint_AnalyzeStatus(PLATFORM_FINGER.status_reg),
            PLATFORM_FINGER.system_id,
            PLATFORM_FINGER.capacity,
            PLATFORM_FINGER.security_level,
            PLATFORM_FINGER.device_addr,
            PLATFORM_FINGER.packet_len,
            PLATFORM_FINGER.baud_rate);
    }
    else
    {
        PLATFORM_SERIAL.println("[ָ��ģ��]:�������ʧ��");
    }
}
/**
 * @author  @Varocol
 * @brief   ״̬����
 * @param   uint8_t     status_code
 * @return  ״̬��Ӧ����Ϣ
 */
const char *FingerPrint_AnalyzeStatus(uint16_t status_code)
{
    switch (status_code)
    {
    case FINGERPRINT_OK:
        return "ָ��ģ���Ѿ���";
    case FINGERPRINT_PACKETRECIEVEERR:
        return "ָ�����ݰ�����";
    case FINGERPRINT_NOFINGER:
        return "û�п�ʶ�����ָ";
    case FINGERPRINT_IMAGEFAIL:
        return "ָ��ͼ�����";
    case FINGERPRINT_FEATUREFAIL:
        return "ָ��������ȱʧ";
    case FINGERPRINT_NOMATCH:
        return "ָ�Ʋ�ƥ��";
    case FINGERPRINT_NOTFOUND:
        return "�Ҳ�����ָ��";
    case FINGERPRINT_ENROLLMISMATCH:
        return "����¼��ָ�Ʋ�ƥ��";
    case FINGERPRINT_BADLOCATION:
        return "ָ���޷��洢�ڸ�λ��";
    case FINGERPRINT_DBRANGEFAIL:
        return "ָ��ģ���ȡʧ��";
    case FINGERPRINT_UPLOADFEATUREFAIL:
        return "ָ��ģ���ϴ�ʧ��";
    case FINGERPRINT_PACKETRESPONSEFAIL:
        return "ָ�����ݰ���Ӧʧ��";
    case FINGERPRINT_UPLOADFAIL:
        return "ָ��ͼ���ϴ�ʧ��";
    case FINGERPRINT_DELETEFAIL:
        return "ָ��ģ��ɾ��ʧ��";
    case FINGERPRINT_DBCLEARFAIL:
        return "���ָ�ƿ�ʧ��";
    case FINGERPRINT_PASSFAIL:
        return "ָ��ģ���������";
    case FINGERPRINT_INVALIDIMAGE:
        return "ͼ�����";
    case FINGERPRINT_FLASHERR:
        return "����д�����";
    case FINGERPRINT_INVALIDREG:
        return "����ļĴ�����ַ";
    case FINGERPRINT_TIMEOUT:
        return "ͨѶ��ʱ";
    case FINGERPRINT_BADPACKET:
        return "���ݰ�����";
    case FINGERPRINT_UNKOWNERR:
        return "δ֪�Ĵ���";
    case FINGERPRINT_REGCONTENTERR:
        return "�Ĵ����趨���ݴ���";
    case FINGERPRINT_PAGERANGEERR:
        return "���±�ҳ��ָ������";
    case FINGERPRINT_COMOPERATEERR:
        return "�˿ڲ���ʧ��";
    case FINGERPRINT_AUTOENROLLERR:
        return "�Զ�ע��(enroll)ʧ��";
    case FINGERPRINT_DBFULL:
        return "ָ�ƿ���";
    default:
        return "δ֪��״̬";
    }
}

/**
 * @author  @Varocol
 * @brief   ָ��¼��(�������ָ����¼��)
 * @param   input_id ѧ��
 * @return  ��
 */
void FingerPrint_Enroll(String input_id)
{
    uint8_t status;
    LCD_print("t0.txt=\"�������ָ���ƴ�����\""); //��ʾ��Ϣ
    LCD_print("backtim.en=0");                    //������ʾоƬ����
    //�ȴ���ָ����
    while (PLATFORM_FINGER.getImage() == FINGERPRINT_NOFINGER)
        delay(1);
    //���ָ���Ƿ��Ѵ���ָ�ƿ�
    if (PLATFORM_FINGER.autoIdentify() == FINGERPRINT_OK)
    {
        String school_id = finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.school_id].as<String>();
        uint32_t operations_cnt = finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.operations_cnt].as<uint32_t>();
        PLATFORM_SERIAL.printf(
            "[ָ��ģ��]:ָ�ƿ����и�ָ��\n"
            "[ָ��ģ��]:[ָ��ID:%d|ƥ���:%d|ѧ��:%s|��������:%d]\n",
            PLATFORM_FINGER.fingerID,
            PLATFORM_FINGER.confidence,
            school_id.c_str(),
            operations_cnt);
        PLATFORM_SERIAL.println("<---------------------------------->");
        show_tips("¼��ʧ��", "ָ�ƿ����и�ָ��\\r[ָ��ID:" + String(PLATFORM_FINGER.fingerID) + "|ѧ��:" + school_id.c_str() + "|ƥ���:" + String(PLATFORM_FINGER.confidence) + "]", "2");
        return;
    }
#if FINGER_AUTOENROLL
    while ((status = PLATFORM_FINGER.autoEnroll()) != FINGERPRINT_OK)
    {
        PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
    }
    uint16_t pos = PLATFORM_FINGER.autoEnrollindex;
#else
    for (int i = 1; i <= 2; i++)
    {
        PLATFORM_SERIAL.printf("�ɼ�������ģ��%d\n", i);
        PLATFORM_SERIAL.println("ͼ��ɼ���");

        //�ɼ�������ģ��1��ͼ��
        while ((status = PLATFORM_FINGER.getImage()) != FINGERPRINT_OK)
        {
            PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
        }
        PLATFORM_SERIAL.println("ͼ��ɼ����");
        //��ͼ��ת����ģ��
        if ((status = PLATFORM_FINGER.image2Tz(i)) != FINGERPRINT_OK)
        {
            PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
            PLATFORM_SERIAL.println("<---------------------------------->");
            return status;
        }
        PLATFORM_SERIAL.printf("������ģ��%dת���ɹ�\n", i);
        if (i == 1)
        {
            //����ģ��1�Ƿ��Ѵ���ָ�ƿ�
            if ((status = PLATFORM_FINGER.fingerFastSearch()) == FINGERPRINT_OK)
            {
                String school_id = finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.school_id].as<String>();
                uint32_t operations_cnt = finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.operations_cnt].as<uint32_t>();
                PLATFORM_SERIAL.printf(
                    "ָ�ƿ����и�ָ��\n"
                    "[ָ��ID:%d|ƥ���:%d|ѧ��:%s|��������:%d]\n",
                    PLATFORM_FINGER.fingerID,
                    PLATFORM_FINGER.confidence,
                    school_id.c_str(),
                    operations_cnt);
                PLATFORM_SERIAL.println("<---------------------------------->");
                return status;
            }
            PLATFORM_SERIAL.printf("������ģ��%d�������,���ÿ���ָ\n", i);
            delay(1000);

            //�ȴ���ָ�ÿ�
            while (PLATFORM_FINGER.getImage() != FINGERPRINT_NOFINGER)
                ;

            PLATFORM_SERIAL.println("���·���ͬһ����ָ");
        }
    }
    //����������ģ��ת����ɺ����ϲ��γɿ��õ�ģ��
    PLATFORM_SERIAL.printf("Ϊָ�ƴ���ģ����...\n");
    if ((status = PLATFORM_FINGER.createModel()) != FINGERPRINT_OK)
    {
        PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
        PLATFORM_SERIAL.println("<---------------------------------->");
        return status;
    }
    PLATFORM_SERIAL.println("����ָ��ƥ��ɹ�");
    //����ָ�ƿ�
    PLATFORM_SERIAL.println("����ָ�ƿ�");
    //���ҿ��Դ洢�Ĳ�λ
    uint16_t pos;
    for (pos = 0; pos < PLATFORM_FINGER.IndexTable.size() && pos == PLATFORM_FINGER.IndexTable[pos]; pos++)
        ;
    if ((status = PLATFORM_FINGER.storeModel(pos)) != FINGERPRINT_OK)
    {
        PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
        PLATFORM_SERIAL.println("<---------------------------------->");
        return status;
    }
#endif
    LCD_print("t0.txt=\"ʶ��ɹ������Ժ�\""); //��ʾ��Ϣ
    PLATFORM_SERIAL.printf("[ָ��ģ��]:ָ��¼��IDΪ%d\n", pos);
    PLATFORM_SERIAL.println("[ָ��ģ��]:ָ��¼��ɹ�");
    //�������ֵ(ѧ��,����)
    JsonObject property = finger_data.createNestedObject(String(pos));
    property[finger_keys.school_id] = input_id;
    property[finger_keys.operations_cnt] = 0;
    //����ָ��������
    FingerPrint_GetIndexTable();
    //���´洢�ļ���������
    FingerPrint_WriteList();
    show_tips("¼��ɹ�", "ѧ��: " + input_id + " �Ǽǳɹ�\\rָ��ID: " + String(pos), "2");
    return;
}

/**
 * @author  @Varocol
 * @brief   ָ��ɾ��
 * @param   input_id ѧ��
 * @return  ��
 */
void FingerPrint_Delete(String input_id)
{
    //��ID��ʼ��Ϊ����ֵ(Խ��ֵ)
    uint8_t status;
    vector<String> data;

    FingerPrint_NumSearch(data, input_id);
    if (data.size() != 0)
    {
        for (String el : data)
        {
            if ((status = PLATFORM_FINGER.deleteModel(el.toInt())) != FINGERPRINT_OK)
            {
                PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
            }
            else
            {
                //ɾ������
                finger_data.remove(el);
                PLATFORM_SERIAL.println("[ָ��ģ��]:ɾ��ָ��ID" + el + "�ɹ�");
                show_tips("ɾ���ɹ�", "ѧ��: " + input_id + "\\rָ��ID: " + el, "2");
            }
        }
        //����ָ��������
        FingerPrint_GetIndexTable();
        //���´洢�ļ���������
        FingerPrint_WriteList();
    }
    else
    {
        PLATFORM_SERIAL.println("[ָ��ģ��]:û�п���ɾ����ָ��");
        show_tips("ɾ��ʧ��", "û�п���ɾ����ָ��", "2");
    }
    return;
}
/**
 * @author  @Varocol
 * @brief   ָ��ID����
 * @param   None
 * @return  ָ��ģ��״̬��
 */
uint16_t FingerPrint_IDSearch()
{
    uint8_t status;
    // int8_t mode;
    // PLATFORM_SERIAL.println("<-------------ָ�Ʋ���------------->");
    // PLATFORM_SERIAL.printf(
    //     "���������ģʽ:\n"
    //     "%d.ָ�Ʋ���ID\n"
    //     "%d.ѧ�Ų���ID\n",
    //     Finger_Search_FingerPrint,
    //     Finger_Search_Name);
    // mode = ReadOption().toInt();
    // if (mode == Finger_Search_FingerPrint)
    // {
    //     FingerPrint_Search();
    // }
    // else if (mode == Finger_Search_Name)
    // {
    //     vector<String> data;
    //     FingerPrint_NumSearch(data);
    //     PLATFORM_SERIAL.printf("���ҵ�%d������\n", data.size());
    //     for (String el : data)
    //     {
    //         PLATFORM_SERIAL.println(el);
    //     }
    // }
    // PLATFORM_SERIAL.println("<---------------------------------->");
    return status;
}
/**
 * @author  @Varocol
 * @brief   ָ�Ʋ���(ͨ��ָ������)
 * @param   None
 * @return  ָ��ģ��״̬��
 */
uint16_t FingerPrint_Search()
{
    uint8_t status;
    PLATFORM_SERIAL.println("[ָ��ģ��]:��ʼ����ָ��");
    PLATFORM_SERIAL.println("[ָ��ģ��]:�ȴ���ָ����...");
    //�ȴ���ָ����
    while (PLATFORM_FINGER.getImage() == FINGERPRINT_NOFINGER)
        delay(1);
#if FINGER_AUTOIDENTIFY
    // ֱ������
    status = PLATFORM_FINGER.autoIdentify();
#else
    //�ɼ�������ģ��1��ͼ��
    while ((status = PLATFORM_FINGER.getImage()) != FINGERPRINT_OK)
    {
        PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
    }
    PLATFORM_SERIAL.println("ͼ��ɼ����");
    //��ͼ��ת����ģ��
    if ((status = PLATFORM_FINGER.image2Tz()) != FINGERPRINT_OK)
    {
        PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
        return status;
    }
    PLATFORM_SERIAL.println("ģ��ת���ɹ�");
    //���ٲ���ָ�ƿ�
    status = PLATFORM_FINGER.fingerFastSearch();
#endif
    //�ҵ�ָ��
    if (status == FINGERPRINT_OK)
    {
        String school_id = finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.school_id].as<String>();
        uint32_t operations_cnt = finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.operations_cnt].as<uint32_t>();
        PLATFORM_SERIAL.printf(
            "[ָ��ģ��]:�ҵ�ָ��\n"
            "[ָ��ģ��]:[ָ��ID:%d|ƥ���:%d|ѧ��:%s|��������:%d]\n",
            PLATFORM_FINGER.fingerID,
            PLATFORM_FINGER.confidence,
            school_id.c_str(),
            operations_cnt);
        finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.operations_cnt] = operations_cnt + 1;
        FingerPrint_WriteList();
        show_tips("��ʾ", "��ӭ ѧ��:" + school_id + "\\rָ��ID:" + String(PLATFORM_FINGER.fingerID) + "\\rƥ��÷�:" + String(PLATFORM_FINGER.confidence), "0");
    }
    //û�и�ָ��
    else if (status == FINGERPRINT_NOTFOUND)
    {
        PLATFORM_SERIAL.println("[ָ��ģ��]:ָ�ƿ���û�и�ָ��");
        show_tips("��ʾ", "��Чָ��", "0");
    }
    //���ҳ���
    else
    {
        PLATFORM_SERIAL.println("[ָ��ģ��]:ƥ�����");
        PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
        show_tips("������", FingerPrint_AnalyzeStatus(status), "0");
    }
    return status;
}
/**
 * @author  @Varocol
 * @brief   ָ�Ʋ���(ͨ��ѧ������)
 * @param   data            ���ڴ�����ҽ��������
 * @return  ָ��ģ��״̬��
 */
void FingerPrint_NumSearch(vector<String> &data, String input_id)
{
    //�������޸�ѧ�ŵ�ָ��
    for (uint16_t el : PLATFORM_FINGER.IndexTable)
    {
        if (finger_data[String(el)][finger_keys.school_id].as<String>() == input_id)
        {
            data.push_back(String(el));
        }
    }
}

/**
 * @author  @Varocol
 * @brief   ���ļ�ϵͳ�м�������
 * @param   None
 * @return  None
 */
void FingerPrint_LoadList()
{
    PLATFORM_SERIAL.print("[�ļ�ϵͳ]:��SPIFFS�ļ�ϵͳ");
    uint8_t time_limit = FINGER_TIMELIMIT;
    while (!SPIFFS.begin() && time_limit)
    {
        PLATFORM_SERIAL.print("...");
        time_limit--;
    }
    PLATFORM_SERIAL.println();
    if (time_limit == 0)
    {
        PLATFORM_SERIAL.println("[�ļ�ϵͳ]:SPIFFS�ļ�ϵͳ�޷���");
        return;
    }
    else
    {
        PLATFORM_SERIAL.println("[�ļ�ϵͳ]:SPIFFS�ļ�ϵͳ�򿪳ɹ�");
    }
    PLATFORM_SERIAL.println("[�ļ�ϵͳ]:���ļ�ϵͳ��������");
    //�����ļ�
    finger_file = SPIFFS.open(FINGER_DATA_PATH, "r", true);
    DynamicJsonDocument tmp(2048);
    DeserializationError error = deserializeJson(tmp, finger_file.readString());
    // JSON�����л���ȡ����
    if (error)
    {
        PLATFORM_SERIAL.println(error.c_str());
        PLATFORM_SERIAL.println("[�ļ�ϵͳ]:���ݷ����л�ʧ��,���ʽ������");
    }
    else
    {
        PLATFORM_SERIAL.println("[�ļ�ϵͳ]:���ݼ��سɹ�");
    }
    //��������ϲ�(��Ҫ��ȡ������)
    for (uint16_t el : PLATFORM_FINGER.IndexTable)
    {
        String school_id = tmp[String(el)][finger_keys.school_id].as<String>();
        if (school_id == "null")
        {
            school_id = FINGER_KEYDEFAULTVALUE;
        }
        finger_data[String(el)][finger_keys.school_id] = school_id;
        finger_data[String(el)][finger_keys.operations_cnt] = tmp[String(el)][finger_keys.operations_cnt].as<uint32_t>();
    }
    //�ر��ļ�
    finger_file.close();
    //�ر��ļ�ϵͳ
    SPIFFS.end();
}

/**
 * @author  @Varocol
 * @brief   д���ļ�ϵͳ
 * @param   None
 * @return  None
 */
void FingerPrint_WriteList()
{
    PLATFORM_SERIAL.print("[�ļ�ϵͳ]:��SPIFFS�ļ�ϵͳ");
    uint8_t time_limit = FINGER_TIMELIMIT;
    while (!SPIFFS.begin() && time_limit)
    {
        PLATFORM_SERIAL.print("...");
        time_limit--;
    }
    PLATFORM_SERIAL.println();
    if (time_limit == 0)
    {
        PLATFORM_SERIAL.println("[�ļ�ϵͳ]:SPIFFS�ļ�ϵͳ�޷���");
    }
    else
    {
        PLATFORM_SERIAL.println("[�ļ�ϵͳ]:SPIFFS�ļ�ϵͳ�򿪳ɹ�");
    }
    //д���ļ�
    finger_file = SPIFFS.open(FINGER_DATA_PATH, "w", true);
    // JSON���л��洢����
    String output;
    serializeJson(finger_data, output);
    finger_file.print(output);
    PLATFORM_SERIAL.println(output);
    //�ر��ļ�
    finger_file.close();
    PLATFORM_SERIAL.println("[�ļ�ϵͳ]:����д��ɹ�");
    //�ر��ļ�ϵͳ
    SPIFFS.end();
}

/**
 * @author  @Varocol
 * @brief   ��ȡָ��������
 * @param   None
 * @return  None
 */
void FingerPrint_GetIndexTable()
{
    PLATFORM_SERIAL.println("[ָ��ģ��]:��ȡָ��������");
    uint8_t status;
    //��ȡָ�ƿ�������
    uint8_t time_limit = FINGER_TIMELIMIT;
    while ((status = PLATFORM_FINGER.readIndexTable()) != FINGERPRINT_OK && time_limit != 0)
    {
        //״̬����
        PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
        //��ʱ100ms
        delay(100);
        time_limit--;
    }
    if (time_limit == 0)
    {
        PLATFORM_SERIAL.println("[ָ��ģ��]:ָ�ƿ����������ʧ��");
        return;
    }
    PLATFORM_SERIAL.println("[ָ��ģ��]:ָ�ƿ���������³ɹ�");
}
/**
 * @author  @Varocol
 * @brief   �޸�ָ����Ϣ
 * @param   None
 * @return  None
 */
void FingerPrint_Alert()
{
    // PLATFORM_SERIAL.println("<-------------ָ���޸�------------>");
    // PLATFORM_SERIAL.println("����ָ���޸�ѧ��");
    // if (FingerPrint_Search() == FINGERPRINT_OK)
    // {
    //     PLATFORM_SERIAL.println("������ѧ��:");
    //     String num = ReadOption();
    //     finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.school_id] = num;
    //     PLATFORM_SERIAL.println("ѧ���޸ĳɹ�");
    //     FingerPrint_WriteList();
    // }
    // PLATFORM_SERIAL.println("<--------------------------------->");
}

/**
 * @author  @Varocol
 * @brief   չʾָ��������
 * @param   None
 * @return  None
 */
void FingerPrint_ShowList()
{
    PLATFORM_SERIAL.println("<-------------ָ��������------------>");
    for (uint16_t el : PLATFORM_FINGER.IndexTable)
    {
        PLATFORM_SERIAL.printf(
            "[ָ��ID:%d|ѧ��:%s|��������:%d]\n",
            el,
            finger_data[String(el)][finger_keys.school_id].as<String>().c_str(),
            finger_data[String(el)][finger_keys.operations_cnt].as<uint32_t>());
    }
    PLATFORM_SERIAL.println("<----------------------------------->");
}

/**
 * @author  @Varocol
 * @brief   ���ָ�ƿ�
 * @param   None
 * @return  None
 */
void FingerPrint_ClearDB()
{
    PLATFORM_SERIAL.println("[ָ��ģ��]:���ָ�ƿ�");
    uint8_t time_limit = FINGER_TIMELIMIT;
    uint8_t status;
    while ((status = PLATFORM_FINGER.emptyDatabase()) != FINGERPRINT_OK && time_limit)
    {
        PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
        time_limit--;
    }
    if (time_limit == 0)
    {
        PLATFORM_SERIAL.println("[ָ��ģ��]:ָ�ƿ�ɾ��ʧ��");
    }
    else
    {
        PLATFORM_SERIAL.println("[ָ��ģ��]:ָ�ƿ�ɾ���ɹ�");
        //ɾ��ѧ�ŵ���Ϣ
        finger_data.clear();
    }
    FingerPrint_WriteList();
}