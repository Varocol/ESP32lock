#include "LCD_callback.h"
#include "Serial_LCD.h"

/**
* ����û�
* @param school_id ��Ļ��������ѧ��
* @return ��
*/
void add_user(String school_id)
{
  LCD_debug("����û�: " + school_id);
}

/**
* ɾ���û�
* @param school_id ��Ļ��������ѧ��
* @return ��
*/
void delete_user(String school_id)
{
  LCD_debug("ɾ���û�: " + school_id);
}

/**
* ���ù���Ա
* @param school_id ��Ļ��������ѧ��
* @return ��
*/
void set_admin(String school_id)
{
  LCD_debug("���ù���Ա: " + school_id);
}

/**
* �޸��û�����
* @param password ��Ļ�������Ľ�������
* @return ��
*/
void change_user_password(String password)
{
  LCD_debug("�޸Ľ�������: " + password);
}

/**
* �޸Ĺ�������
* @param password ��Ļ�������Ľ�������
* @return ��
*/
void change_admin_password(String password)
{
  LCD_debug("�޸Ĺ�������: " + password);
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
}