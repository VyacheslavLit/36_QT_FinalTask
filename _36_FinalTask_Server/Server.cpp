#include "Server.h"



void Server::miServer()
{
    WSADATA wsData;
    int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);
    if (erStat != 0)
    {
        cout << "������ ������������� ������ WinSock #";
        cout << WSAGetLastError();
        return;
    }
    else if (!perepiska) cout << "WinSock ���������������.\n";

    //�������� �����
    sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (sockert_file_descriptor == -1)
    {
        cout << "�������� ������ ��������!\n";
        exit(1);
    }
    memset(&serveraddress, 0, sizeof(serveraddress));
    serveraddress.sin_addr.s_addr = htonl(2130706433);
    //������ ����� ����� ��� �����
    serveraddress.sin_port = htons(PORT);
    //���������� IPv4
    serveraddress.sin_family = AF_INET;
    //�������� �����
    bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (bind_status == -1)
    {
        cout << "�� ������� ��������� �������� ������.!" << endl;
        exit(1);
    }
    //�������� ������ �� ����� ������
    connection_status = listen(sockert_file_descriptor, 5);
    if (connection_status == -1)
    {
        cout << "����� �� ����� ������������ ����� �����������.!" << endl;
        exit(1);
    }
    length = sizeof(client);

    //Communication Establishment - ������������ �����
    string pref;
    while (true)
    {
        if (!perepiska) cout << "������ ������������ ����� ����������:" << " " << connection << endl;
        string mes_suf = "";
        reply.clear();
        mes_suf.clear();
        memset(message, 0, MESSAGE_LENGTH);
        connection = accept(sockert_file_descriptor, (struct sockaddr*)&client, &length);
        if (connection == -1)
        {
            cout << "������ �� ����� ������� ������ �� �������.!" << endl;
            exit(1);
        }
        recv(connection, message, sizeof(message), 0);
        pref = message[0];
        for (int i = 1; i < MESSAGE_LENGTH; i++)
        {
            if (message[i] == '~')break;
            mes_suf = mes_suf + message[i];
        }
        perepiska = false;

        if (pref == "l") zaprosLogin(mes_suf);
        if (pref == "r") zaprosReg(mes_suf);
        if (pref == "m") zapros_Contents_of_the_correspondence_file();//������ �� ������������ ����������� ����� ���������
        if (pref == "n") zapros_from_admin_of_general_correspondence();//������ �� ������ ����������� ����� ����� ���������.
        if (pref == "u") zapros_from_user_list_users();//������ �� ������������ ������� �������������
        if (pref == "y") zapros_from_user_list_users_from_n_name();//������ �� ������������ ������� �������������
        if (pref == "k") zapros_id_n_name_all_users();//������ id, n_name ���� �������������
        if (pref == "e") zapros_name_by_user_id(mes_suf);//������ ����� �� id ������������
        if (pref == "f") zapros_id_by_name_user(mes_suf);//������ id �� ����� ������������
        if (pref == "g") zapros_id_by_login_user(mes_suf);//������ id �� ������ ������������.
        if (pref == "w") zapros_status_by_id_user(mes_suf);//������ ������� ������������ �� id
        if (pref == "i") zapros_status_by_n_name(mes_suf);//������ ������� ������������ �� N_Name
        if (pref == "h") zapros_id_from_id_to_by_personal_cor();//������ id_from, id_to �� ������ ���������
        if (pref == "j") zapros_personal_cor_from_user(mes_suf);//������ ������ ��������� �� ������������
        if (pref == "b") zapros_message_status_by_id(mes_suf);//������ ������� ��������� ����� ��������� �� id
        if (pref == "v") zapros_user_status_changes_by_id(mes_suf);//������ ����� ������� ������������ �� id.
        if (pref == "o") zapros_user_status_changes_by_n_name(mes_suf);//������ ����� ������� ������������ �� n_name.
        if (pref == "a") zapros_mess_status_changes_by_id(mes_suf);//������ ����� ������� ��������� ����� ��������� �� id
        if (pref == "d") zapros_add_mess_from_global_messages(mes_suf);//������ ���������� ��������� ����� ���������
        if (pref == "q") zapros_add_mess_from_messages(mes_suf);//������ ���������� ��������� ������ ���������
        if (pref == "c") zapros_password_change(mes_suf);//������ �� ����� ������
        if (pref == "t") getLog();//������ ����� �����
        memset(message, 0, MESSAGE_LENGTH);
        reply.copy(message, reply.length() + 1);
        auto bytes = send(connection, message, sizeof(message), 0);
        // ���� �������� >= 0 ����, ������ ��������� ������ �������
        if (bytes >= 0)
        {
            if (!perepiska) cout << "������ ������� �������� �������!" << endl;
        }
    }
    //��������� �����, ��������� ����������
    closesocket(sockert_file_descriptor);

    return;
}


void Server::zaprosMySQL(string zapros)
{
    MYSQL mysql;
    MYSQL_RES* res;
    MYSQL_ROW row;

    int i = 0;

    // �������� ���������� ����������
    mysql_init(&mysql);
    if (&mysql == nullptr) {
        // ���� ���������� �� ������� � ������� ��������� �� ������
        cout << "Error: can't create MySQL-descriptor" << endl;
    }

    // ������������ � �������
    if (!mysql_real_connect(&mysql, "localhost", "root", "1111", "chat", NULL, NULL, 0)) {
        // ���� ��� ����������� ���������� ���������� � �� ������� ��������� �� ������
        cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
    }
    else {
        // ���� ���������� ������� ����������� ������� ����� � "Success!"
        if (!perepiska) cout << "Success!" << endl;
    }

    //    mysql_query(&mysql, "set names utf8mb4");
    mysql_query(&mysql, "SET NAMES utf8 COLLATE utf8_unicode_ci;");
    //mysql_query(&mysql, "collation-server = utf8_unicode_ci");


    //������� ���������� �� ��������� �� ������, �� ��������� ��� latin1
    if (!perepiska) cout << "connection characterset: " << mysql_character_set_name(&mysql) << endl;


    if (!perepiska) cout << "������: " << zapros << endl;
    //������������ ��������
    setLog(zapros);

    mysql_query(&mysql, const_cast<char*>(zapros.c_str())); //������ ������ � �������


    if (res = mysql_store_result(&mysql)) {
        while (row = mysql_fetch_row(res)) {
            for (int i = 0; i < mysql_num_fields(res); i++) reply = reply + row[i] + " ";
        }
    }
    if (reply.length() > 0) if (reply[reply.length() - 1] == ' ')reply.pop_back();
    if (!perepiska) cout << "�����: " << reply << endl;
    // ��������� ���������� � �������� ���� ������
    mysql_close(&mysql);
}


void Server::reg(string message)
{
    int i;
    string login, id_user, password, n_name, name, family, email;
    message += '~';
    for (i = 0; i < sizeof(message); i++)
    {
        if (message[i] == ' ') break;
        login += message[i];
    }
    i++;
    for (i; i < sizeof(message); i++)
    {
        if (message[i] == ' ') break;
        password += message[i];
    }
    i++;
    for (i; i < sizeof(message); i++)
    {
        if (message[i] == ' ') break;
        n_name += message[i];
    }
    i++;
    for (i; i < sizeof(message); i++)
    {
        if (message[i] == ' ') break;
        name += message[i];
    }
    i++;
    for (i; i < sizeof(message); i++)
    {
        if (message[i] == ' ') break;
        family += message[i];
    }
    i++;
    for (i; i < sizeof(message); i++)
    {
        if (message[i] == '~') break;
        email += message[i];
    }

    //�������� ������ �� �������
    reply.clear();
    string zapros = "select id from users where login = '" + login + "'";
    zaprosMySQL(zapros);
    if (reply != "")
    {
        reply = "1";
        return;
    }
    //�������� ���������� �� �������
    reply.clear();
    zapros = "select id from users where n_name = '" + n_name + "'";
    zaprosMySQL(zapros);
    if (reply != "")
    {
        reply = "2";
        return;
    }
    //���������� ������ ������������
    reply.clear();
    zapros = "insert users (login, n_name, name, family, email) value ('" + login + "', '" + n_name + "', '" + name + "', '" + family + "', '" + email + "')";
    zaprosMySQL(zapros);
    reply.clear();
    zapros = "select id from users where login = '" + login + "'";
    zaprosMySQL(zapros);
    id_user = reply;
    zapros = "insert pass (id_user, hash) value ('" + id_user + "', '" + password + "')";
    zaprosMySQL(zapros);
    reply = "0";
}




void Server::changPassw(string request)
{
    string n_name;
    string password;
    request += '~';
    int i;
    for (i = 0; i < sizeof(request); i++)
    {
        if (request[i] == ' ')break;
        n_name += request[i];
    }
    i++;
    for (i; i < sizeof(request); i++)
    {
        if (request[i] == '~')break;
        password += request[i];
    }
    zaprosMySQL("update pass p join users u set p.hash = '" + password + "' where p.id_user = (select id from users where n_name = '" + n_name + "')");
    reply = "0";
}



void expCin()
{
    cin.clear();
    cin.ignore(32767, '\n');
    cout << "������ �����, ��������� �������.\n";
    cout << cin.get();
    cin.clear();
    cin.ignore(32767, '\n');
};

void Server::pauses()
{
    cin.clear();
    cin.ignore(32767, '\n');
    cout << endl << "��� ���������� ������� ����� �������.";
    cout << cin.get();//pause
}