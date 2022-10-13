#include "LCD_callback.h"
#include "Serial_LCD.h"
#include <Preferences.h>
#include <Unclock_Servo.h>
#include <FINGERPrint.h>

/**
 * ����û�
 * @param school_id ��Ļ��������ѧ��
 * @return ��
 */
void add_user(String school_id)
{
  LCD_debug("����û�: " + school_id);
  if (school_id.length() < 1 || school_id.length() > 20)
  {
    show_tips("��ʾ", "ѧ�ų���ӦΪ1-20λ\\r����������", "6");
    return;
  }
  // ����ŷ����ָ��¼��ӿ�
  FingerPrint_Enroll(school_id);
}

/**
 * ɾ���û�
 * @param school_id ��Ļ��������ѧ��
 * @return ��
 */
void delete_user(String school_id)
{
  LCD_debug("ɾ���û�: " + school_id);
  if (school_id.length() < 1 || school_id.length() > 20)
  {
    show_tips("��ʾ", "ѧ�ų���ӦΪ1-20λ\\r����������", "6");
    return;
  }
  // ����ŷ����ָ��ɾ���ӿ�
  FingerPrint_Delete(school_id);
}

/**
 * ���ù���Ա
 * @param school_id ��Ļ��������ѧ��
 * @return ��
 */
void set_admin(String school_id)
{
  LCD_debug("���ù���Ա: " + school_id);
  if (school_id.length() < 1 || school_id.length() > 20)
  {
    show_tips("��ʾ", "ѧ�ų���ӦΪ1-20λ\\r����������", "6");
    return;
  }
  show_tips("��ʾ", "�ù�����Ч\\r��ʹ���������˵�", "6");
}

/**
 * �޸��û�����
 * @param password ��Ļ�������Ľ�������
 * @return ��
 */
void change_user_password(String password)
{
  LCD_debug("�޸Ľ�������: " + password);
  if (password.length() != 6)
  {
    show_tips("��ʾ", "���볤��ӦΪ6λ\\r����������", "6");
    return;
  }
  Preferences prefs;                                           // ����Preferences����
  prefs.begin("config");                                       // �������ռ�config
  String real_admin_password = prefs.getString("admin_k", ""); // ��ȡ����Ա����
  if (password == real_admin_password)
  {
    show_tips("��ʾ", "�û����벻�ܺ͹���Ա������ͬ\\r����������", "6");
    return;
  }
  prefs.putString("user_k", password); // д���������
  prefs.end();                         // �ر������ռ�
  show_tips("��ʾ", "�����޸ĳɹ�", "6");
}

/**
 * �޸Ĺ�������
 * @param password ��Ļ�������Ľ�������
 * @return ��
 */
void change_admin_password(String password)
{
  LCD_debug("�޸Ĺ�������: " + password);
  if (password.length() != 6)
  {
    show_tips("��ʾ", "���볤��ӦΪ6λ\\r����������", "6");
    return;
  }
  Preferences prefs;                                         // ����Preferences����
  prefs.begin("config");                                     // �������ռ�config
  String real_user_password = prefs.getString("user_k", ""); // ��ȡ�û�����
  if (password == real_user_password)
  {
    show_tips("��ʾ", "����Ա���벻�ܺ��û�������ͬ\\r����������", "6");
    return;
  }
  prefs.putString("admin_k", password); // д���������
  prefs.end();                          // �ر������ռ�
  show_tips("��ʾ", "�����޸ĳɹ�", "6");
}

/**
 * ��������ص�
 * @param password ��������
 * @return ��
 */
void unlock(String password)
{
  LCD_debug("�������: " + password);
  //�����߼�
  Preferences prefs;                                           // ����Preferences����
  prefs.begin("config");                                       // �������ռ�config
  String real_user_password = prefs.getString("user_k", "");   // ��ȡ�û�����
  String real_admin_password = prefs.getString("admin_k", ""); // ��ȡ����Ա����
  prefs.end();

  //�ж��Ƿ�Ϊ��
  if (real_user_password == "" || real_admin_password == "")
  {
    LCD_debug("����Ϊ��");
    show_tips("�޷�ʹ���������", "������δ����\\r������������", "0");
    return;
  }
  //�ж��Ƿ�Ϊ����Ա����
  if (password == real_admin_password)
  {
    LCD_debug("����Ա�������");
    LCD_print("page 1");
    unclock_servo_open();
    return;
  }
  //�ж��Ƿ�Ϊ�û�����
  if (password == real_user_password)
  {
    LCD_debug("�û��������");
    show_tips("�����ɹ�", "�������", "0");
    unclock_servo_open();
    return;
  }
  show_tips("��ʾ", "��Ч����", "0");
}