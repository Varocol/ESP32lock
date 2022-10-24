#ifndef __WEBSERVER_H
#define __WEBSERVER_H
#include <Arduino.h>

const char main_HTML[] PROGMEM = "<!DOCTYPE html><html lang=zh-cmn-Hans><head><meta charset=\"utf-8\"><meta name=viewport content=\"width=device-width,initial-scale=1,maximum-scale=1,shrink-to-fit=no\"><meta name=renderer content=\"webkit\"><meta name=force-rendering content=\"webkit\"><meta http-equiv=X-UA-Compatible content=\"IE=edge,chrome=1\"><link rel=stylesheet href=\"https://unpkg.com/mdui@1.0.2/dist/css/mdui.min.css\"><title>智能锁管理系统</title><body class=\"mdui-theme-primary-indigo mdui-theme-accent-pink mdui-theme-layout-auto\"><div class=mdui-appbar><div class=\"mdui-toolbar mdui-color-theme\"><a class=mdui-typo-headline>智能锁管理系统</a><div class=mdui-toolbar-spacer></div><a href=https://github.com/liujiaqi7998/ESP32lock target=_blank class=\"mdui-btn mdui-btn-icon mdui-ripple mdui-ripple-white\" mdui-tooltip=\"{content: '查看 Github'}\"><svg version=1.1 id=Layer_1 xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink x=0px y=0px viewbox=\"0 0 36 36\" enable-background=\"new 0 0 36 36\" xml:space=preserve class=mdui-icon style=width:24px;height:24px><path fill-rule=evenodd clip-rule=evenodd fill=#ffffff d=M18,1.4C9,1.4,1.7,8.7,1.7,17.7c0,7.2,4.7,13.3,11.1,15.5c0.8,0.1,1.1-0.4,1.1-0.8c0-0.4,0-1.4,0-2.8c-4.5,1-5.5-2.2-5.5-2.2c-0.7-1.9-1.8-2.4-1.8-2.4c-1.5-1,0.1-1,0.1-1c1.6,0.1,2.5,1.7,2.5,1.7c1.5,2.5,3.8,1.8,4.7,1.4c0.1-1.1,0.6-1.8,1-2.2c-3.6-0.4-7.4-1.8-7.4-8.1c0-1.8,0.6-3.2,1.7-4.4c-0.2-0.4-0.7-2.1,0.2-4.3c0,0,1.4-0.4,4.5,1.7c1.3-0.4,2.7-0.5,4.1-0.5c1.4,0,2.8,0.2,4.1,0.5c3.1-2.1,4.5-1.7,4.5-1.7c0.9,2.2,0.3,3.9,0.2,4.3c1,1.1,1.7,2.6,1.7,4.4c0,6.3-3.8,7.6-7.4,8c0.6,0.5,1.1,1.5,1.1,3c0,2.2,0,3.9,0,4.5c0,0.4,0.3,0.9,1.1,0.8c6.5-2.2,11.1-8.3,11.1-15.5C34.3,8.7,27,1.4,18,1.4z></path></svg></a></div></div><div class=\"container p-ripple mdui-container\"><h1 class=\"title mdui-text-color-theme\">欢迎使用，智能锁管理系统</h1><div class=\"intro mdui-typo\"><ins class=adsbygoogle style=display:block;margin-top:40px data-ad-client=ca-pub-4466345895756968 data-ad-slot=3103002934 data-ad-format=auto data-full-width-responsive=true></ins><script>(adsbygoogle=window.adsbygoogle||[]).push({});</script><p></p><div class=mdui-row><div class=mdui-col-xs-6><div class=mdui-card><div class=mdui-card-primary><div class=mdui-card-primary-title>连接</div><div class=mdui-card-primary-subtitle>请在下方输入安全锁的连接地址和管理员密码</div><div class=mdui-textfield><i class=\"mdui-icon material-icons\">&#xe308;</i> <input id=url class=mdui-textfield-input placeholder=\"http://192.168.x.xx\"></div><div class=mdui-textfield><i class=\"mdui-icon material-icons\">lock</i> <input id=admin_key class=mdui-textfield-input type=password placeholder=\"管理员密码\"></div></div><div class=mdui-card-actions><button id=test_but class=\"mdui-btn mdui-btn-raised mdui-ripple mdui-color-theme-accent\">测试连接</button></div></div></div><div class=mdui-col-xs-6><div class=mdui-card><div class=mdui-card-primary><div class=mdui-card-primary-title>一键解锁</div></div><div class=mdui-card-actions><button id=unlock class=\"mdui-btn mdui-btn-raised mdui-ripple mdui-color-theme-accent\">解锁</button></div></div><p></p><div class=mdui-card><div class=mdui-card-primary><div class=mdui-card-primary-title>OTA升级</div></div><div class=mdui-card-actions><button id=update_but class=\"mdui-btn mdui-btn-raised mdui-ripple mdui-color-theme-accent\">进入</button></div></div></div></div><p></p><div class=mdui-row><div class=mdui-col-xs-6><div class=mdui-card><div class=mdui-card><div class=mdui-card-primary><div class=mdui-card-primary-title>指纹列表</div><div class=mdui-card-primary-subtitle>修改或删除指纹</div></div><div class=mdui-card-content><div class=mdui-table-fluid><table class=\"mdui-table mdui-table-selectable\"><thead><tr><th>ID<th>学号<th>匹配次数<tbody id=finger_table></table></div></div><div class=mdui-card-actions><button id=getlist_but class=\"mdui-btn mdui-btn-raised mdui-ripple mdui-color-theme-accent\">刷新列表</button> <button class=\"mdui-btn mdui-btn-raised mdui-ripple mdui-color-theme-accent\" mdui-dialog=\"{target: '#example-1'}\">修改学号</button> <button id=delid_but class=\"mdui-btn mdui-btn-raised mdui-ripple mdui-color-theme-accent\">删除指纹</button></div></div></div></div><div class=mdui-col-xs-6><div class=mdui-card><div class=mdui-card-primary><div class=mdui-card-primary-title>修改管理员密码</div><div class=mdui-textfield><i class=\"mdui-icon material-icons\">lock</i> <input class=mdui-textfield-input id=admin_key_input type=password placeholder=\"新管理员密码\"></div></div><div class=mdui-card-actions><button id=admin_reset_but class=\"mdui-btn mdui-btn-raised mdui-ripple mdui-color-theme-accent\">提交</button></div></div><p></p><div class=mdui-card><div class=mdui-card-primary><div class=mdui-card-primary-title>修改用户密码</div><div class=mdui-textfield><i class=\"mdui-icon material-icons\">lock</i> <input class=mdui-textfield-input id=user_key_input type=password placeholder=\"新用户密码\"></div></div><div class=mdui-card-actions><button id=user_reset_but class=\"mdui-btn mdui-btn-raised mdui-ripple mdui-color-theme-accent\">提交</button></div></div></div></div></div><p></p><div class=mdui-card><div class=mdui-card-primary><div class=mdui-card-primary-title>控制台</div><div class=mdui-textfield><textarea class=result rows=20 placeholder=\"\" readonly></textarea></div></div><div class=mdui-card-actions><button id=connect_console class=\"mdui-btn mdui-btn-raised mdui-ripple mdui-color-theme-accent\">连接</button></div></div></div><div class=mdui-dialog id=example-1><div class=mdui-dialog-title>请输入要修改成的学号</div><div class=mdui-dialog-content><div class=mdui-textfield><i class=\"mdui-icon material-icons\">account_circle</i> <input class=mdui-textfield-input id=student_input placeholder=\"新学号\"></div></div><div class=mdui-dialog-actions><button class=\"mdui-btn mdui-ripple\" mdui-dialog-close>取消</button> <button class=\"mdui-btn mdui-ripple\" id=changeid_but mdui-dialog-confirm>确认</button></div></div><div class=mdui-dialog id=example-2><div class=mdui-dialog-title><div class=mdui-progress><div class=mdui-progress-indeterminate></div></div></div><div class=mdui-dialog-content>加载中，请稍后...</div></div><script src=https://unpkg.com/mdui@1.0.2/dist/js/mdui.min.js></script><script>function onOpen(){writelog(\"已连接\",\"system\")}function onClose(){writelog(\"连接已断开\",\"system\")}function onMessage(e){writelog(e.data,\"server\")}function onError(e){writelog(\"错误:\"+e.data,\"system\")}function sendmessage(e){writelog(e,\"client\"),websocket.send(e)}function writelog(e,t){switch(t){case\"client\":name=\"客户端：\";break;case\"server\":name=\"服务器端：\";break;case\"system\":name=\"系统信息：\"}var n=new Date;Y=n.getFullYear()+\"-\",M=(n.getMonth()+1<10?\"0\"+(n.getMonth()+1):n.getMonth()+1)+\"-\",D=(n.getDate()<10?\"0\"+n.getDate():n.getDate())+\" \",h=(n.getHours()<10?\"0\"+n.getHours():n.getHours())+\":\",m=(n.getMinutes()<10?\"0\"+n.getMinutes():n.getMinutes())+\":\",s=n.getSeconds()<10?\"0\"+n.getSeconds():n.getSeconds(),$(\"#result\").text($(\"#result\").text()+name+\" \"+(Y+M+D+h+m+s)+\"\\n\"+e+\"\\n\\n\")}function send_data(e,t,n){var o=$(\"#url\").val(),i=$(\"#admin_key\").val();return localStorage.setItem(\"admin_key\",i),\"\"==o?void mdui.alert(\"请先输入连接地址\"):\"\"==i?void mdui.alert(\"请先输入管理员密码\"):(t.admin_key=i,inst.open(),void $.ajax({method:\"GET\",url:o+\"/\"+e,data:t,success:function(e){inst.close(),console.log(e),testJson=JSON.parse(e),null!=testJson.e&&(-1!=String(testJson.e).search(\"成功\")&&void 0!=n&&n(),mdui.alert(testJson.e,\"提示\"))},error:function(e,t){inst.close(),mdui.alert(\"请求失败:\"+t,\"错误\"),console.log(e)}}))}function Refresh_list(){var e=$(\"#url\").val(),t=$(\"#admin_key\").val();if(localStorage.setItem(\"admin_key\",t),\"\"==e)return void mdui.alert(\"请先输入连接地址\");if(\"\"==t)return void mdui.alert(\"请先输入管理员密码\");var n={admin_key:t};inst.open(),$.ajax({method:\"GET\",url:e+\"/getlist\",data:n,success:function(e){inst.close();var t=JSON.parse(e);null!=t.e?mdui.alert(t.e,\"提示\"):showlist(t)},error:function(e,t){inst.close(),mdui.alert(\"请求失败:\"+t,\"错误\"),console.log(e)}})}function showlist(e){$(\"#finger_table\").html(\"\");var t=\"\";for(var n in e)t+=\"<tr>\",t+=\"<td>\"+n+\"</td>\",t+=\"<td>\"+e[n].school_id+\"</td>\",t+=\"<td>\"+e[n].operations_cnt+\"</td>\",t+=\"</tr>\";$(\"#finger_table\").html(t),mdui.updateTables(\".mdui-table\"),mdui.snackbar({message:\"列表刷新成功！\",position:\"bottom\"})}var $=mdui.$,loca_url=\"http://\"+window.location.host;$(\"#url\").val(loca_url),$(\"#admin_key\").val(localStorage.getItem(\"admin_key\"));var inst=new mdui.Dialog(\"#example-2\",{overlay:!1,history:!1,modal:!0,closeOnEsc:!1});$(\"#connect_console\").on(\"click\",function(){var e=new RegExp(/\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}/);wsUri=\"ws://\"+String($(\"#url\").val()).match(e)+\"/ws\",console.log(wsUri),websocket=new WebSocket(wsUri),websocket.onopen=function(e){onOpen(e)},websocket.onclose=function(e){onClose(e)},websocket.onmessage=function(e){onMessage(e)},websocket.onerror=function(e){onError(e)}}),$(\"#delid_but\").on(\"click\",function(){mdui.confirm(\"确认删除吗？\",\"警告\",function(){for(var e=new Array,t=document.getElementById(\"finger_table\"),n=t.getElementsByTagName(\"tr\"),o=0;o<n.length;o++){var i=n[o].getElementsByTagName(\"td\");i[0].getElementsByTagName(\"input\")[0].checked&&e.push(i[1].innerText)}send_data(\"del_finger\",{list:JSON.stringify(e)},Refresh_list)},function(){},{confirmText:\"确认\",cancelText:\"取消\"})}),$(\"#changeid_but\").on(\"click\",function(){for(var e=$(\"#student_input\").val(),t=new Array,n=document.getElementById(\"finger_table\"),o=n.getElementsByTagName(\"tr\"),i=0;i<o.length;i++){var s=o[i].getElementsByTagName(\"td\");s[0].getElementsByTagName(\"input\")[0].checked&&t.push(s[1].innerText)}send_data(\"alert_finger\",{list:JSON.stringify(t),new_id:e},Refresh_list)}),$(\"#getlist_but\").on(\"click\",function(){mdui.snackbar({message:\"获取中，请稍后...\",position:\"bottom\"}),Refresh_list()}),$(\"#unlock\").on(\"click\",function(){mdui.snackbar({message:\"已发送解锁请求\",position:\"bottom\"}),send_data(\"unlock\",{})}),$(\"#test_but\").on(\"click\",function(){mdui.snackbar({message:\"测试中，请稍后...\",position:\"bottom\"}),send_data(\"test\",{})}),$(\"#update_but\").on(\"click\",function(){var e=$(\"#url\").val();return\"\"==e?void mdui.alert(\"请先输入连接地址\"):void(window.location.href=e+\"/update\")}),$(\"#admin_reset_but\").on(\"click\",function(){var e=$(\"#admin_key_input\").val();return 6!=e.length||isNaN(e)?void mdui.alert(\"密码必须为6位数字\"):void mdui.dialog({title:\"提示\",content:\"确认要修改管理员密码为\"+e+\"吗？\",buttons:[{text:\"取消\"},{text:\"确认\",onClick:function(){mdui.snackbar({message:\"已发送解锁请求\",position:\"bottom\"}),send_data(\"set_admin_key\",{new_admin_key:e})}}]})}),$(\"#user_reset_but\").on(\"click\",function(){var e=$(\"#user_key_input\").val();return 6!=e.length||isNaN(e)?void mdui.alert(\"密码必须为6位数字\"):void mdui.dialog({title:\"提示\",content:\"确认要修改用户密码为\"+e+\"吗？\",buttons:[{text:\"取消\"},{text:\"确认\",onClick:function(){mdui.snackbar({message:\"已发送解锁请求\",position:\"bottom\"}),send_data(\"set_user_key\",{new_user_key:e})}}]})});</script>";
void int_web();
#endif //__WEBSERVER_H