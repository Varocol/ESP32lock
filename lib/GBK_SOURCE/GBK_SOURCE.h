#ifndef __GBK_SOURCE_H
#define __GBK_SOURCE_H
#include <Arduino.h>
static String debug_screen_msg = "调试屏幕中";
static String debug_fingerprint_msg = "调试指纹模块中";
static String place_finger_msg = "请放置手指到纹传感器";
static String recognize_sucess_msg = "识别成功，请稍后";
static String wait_msg = "请稍后";
static String school_id_msg_1 = "  学号:";
static String school_id_msg_2 = "学号: ";
static String serious_error_msg = "严重错误";
static String fingerprint_error_msg = "未能找到指纹识别模块\\r请重启";
static String enroll_fail_msg = "录入失败";
static String enroll_success_msg = "录入成功";
static String finger_id_msg = "\\r指纹ID:";
static String find_fingerprint_msg = "指纹库已有该指纹" + finger_id_msg;
static String confident_msg = "\\r匹配度:";
static String register_success_msg = " 登记成功" + finger_id_msg + " ";
static String tip_msg = "提示";
static String welcome_msg = "欢迎 学号:";
static String invalid_finger_msg = "无效指纹";
static String retry_msg = "请重试";
static String delete_success_msg = "删除成功";
static String school_id_len_error_msg = "学号长度应为1-20位\\r请重新设置";
static String password_len_error_msg = "密码长度应为6位\\r请重新设置";
static String function_invalid_msg = "该功能无效\\r请使用密码进入菜单";
static String password_invalid_msg_1 = "用户密码不能和管理员密码相同\\r请重新设置";
static String password_invalid_msg_2 = "管理员密码不能和用户密码相同\\r请重新设置";
static String alert_pass_success_msg = "密码修改成功";
static String pass_error_msg = "无法使用密码解锁";
static String pass_unset_msg = "有密码未设置\\r请先设置密码";
static String unlock_success_msg = "解锁成功";
static String pass_unlock_msg = "密码解锁";
static String invalid_pass_msg = "无效密码";
static String fingerprint_empty_msg = "指纹库为空";
static String network_config_suceess_msg = "配网成功，请重启";
#endif // !__GBK_SOURCE_H
