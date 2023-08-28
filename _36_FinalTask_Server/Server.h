#pragma once
#include <iostream>
#include <string>
#include <map>
#include <string.h>
#include <thread>
//#include <functional>
#include "Times.h"
#include "Logger.h"

#ifdef __Linux__
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#elif defined(_WIN32)||defined(_WIN64)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <mysql.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
#include <iphlpapi.h>
#pragma comment(lib, "Ws2_32.lib")
#else 
#error Not implemented!
#endif

using namespace std;

#define MESSAGE_LENGTH 1024 //максимальныйразмер буфера для данных
#define PORT 7777 //будем использовать этот номер порта

class Server
{
private:
    std::shared_mutex mu;
    struct sockaddr_in serveraddress, client;
    socklen_t length;
    int sockert_file_descriptor, connection, bind_status, connection_status;
    char message[MESSAGE_LENGTH];
    string reply;
    Logger Logg;
    void setLog(string Log) { Logg.setLog(Log); }
    void getLog() { reply = Logg.getLog(); }
public:
    Server()
    {
    }
    ~Server() {}
    void miServer();
private:
    void zaprosMySQL(string);
    void reg(string);
    void changPassw(string pass);
    void pauses();
    void zaprosLogin(string);
    void zaprosReg(string);
    void zapros_Contents_of_the_correspondence_file();//Запрос от пользователя содержимого файла переписки
    void zapros_from_admin_of_general_correspondence();//Запрос от админа содержимого файла общей переписки.
    void zapros_from_user_list_users();//Запрос от пользователя перечня пользователей
    void zapros_from_user_list_users_from_n_name();//Запрос от пользователя перечня пользователей
    void zapros_id_n_name_all_users();//запрос id, n_name всех пользователей
    void zapros_name_by_user_id(string);//Запрос имени по id пользователя
    void zapros_id_by_name_user(string);//запрос id по имени пользователя
    void zapros_id_by_login_user(string);//запрос id по логину пользователя.
    void zapros_status_by_id_user(string);//Запрос статуса пользователя по id
    void zapros_status_by_n_name(string);//Запрос статуса пользователя по n_name
    void zapros_id_from_id_to_by_personal_cor();//Запрос id_from, id_to из личной переписки
    void zapros_personal_cor_from_user(string);//Запрос личной переписки по 2 пользователям
    void zapros_message_status_by_id(string);//Запрос статуса сообщения общей переписки по id
    void zapros_user_status_changes_by_id(string);//запрос смены статуса пользователя по id.
    void zapros_user_status_changes_by_n_name(string);//запрос смены статуса пользователя по n_name
    void zapros_mess_status_changes_by_id(string);//запрос смены статуса сообщения общей переписки по id
    void zapros_add_mess_from_global_messages(string);//запрос добавление сообщения общей переписки
    void zapros_add_mess_from_messages(string);//запрос добавление сообщения личной переписки
    void zapros_password_change(string);//Запрос на смену пароля

    bool perepiska;
};
