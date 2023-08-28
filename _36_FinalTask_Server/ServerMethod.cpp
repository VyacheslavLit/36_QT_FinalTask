#include "Server.h"


void Server::zaprosLogin(string mes_suf)
{
    reply = "";
    string log;
    log = time() + " ������ �� ������������ �� �����.";
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    //��������� �� ������� ������ � ������
    int i;
    string _login, password;
    for (i = 0; i < mes_suf.length(); i++)
    {
        if (mes_suf[i] == ' ') break;
        _login += mes_suf[i];
    }
    i++;
    for (i; i < mes_suf.length(); i++)
    {
        password += mes_suf[i];
    }
    //������ � SQL, n_name, status, pass �� ������
    zapros = "select n_name, status, hash from login_pass where login = '" + _login + "';";
    zaprosMySQL(zapros);
    string n_name, status, hash;
    for (i = 0; i < reply.size(); i++) if (reply[i] != ' ') n_name += reply[i]; else
    {
        i++;
        break;
    }
    for (i; i < reply.size(); i++) if (reply[i] != ' ') status += reply[i]; else
    {
        i++;
        break;
    }
    for (i; i < reply.size(); i++) if (reply[i] != ' ') hash += reply[i];
    //������ ������ � �����
    if (password != hash)
    {
        log = " ����� ������������ �� ������.";
        reply = "0";
    }
    else
        if (status == "2")
        {
            log = " ������������ �������, ����� ��������.";
            reply = "b";
        }
        else
        {
            reply = n_name;
            log = " ����� ������������ " + reply + " �������.";
        }
    zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
}

void Server::zaprosReg(string mes_suf)
{
    string log;
    log = time() + " ������ �� ������������ �� �����������.";
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    cout << log << endl;
    reg(mes_suf);
    if (reply == "0")log = time() + " ����������� ������������ ��������.";
    if (reply == "1" || reply == "2") log = time() + " ����������� ������������ �� ������.";
    zaprosMySQL("insert log (log) value ('" + log + "');");
}

void Server::zapros_Contents_of_the_correspondence_file()//������ �� ������������ ����������� ����� ���������
{
    perepiska = true;
    string zapros = "select u.n_name, '\t', m.date, '\t', m.text, '\n' from global_message m join users u on m.id_from = u.id where m.status = 1;";
    zaprosMySQL(zapros);
}

void Server::zapros_from_admin_of_general_correspondence()
{
    string log;
    log = time() + " ������ �� ������ ����������� ����� ����� ���������.";
    string zapros = "insert log (log) value ('" + log + "');";

    zaprosMySQL(zapros);
    cout << log << endl;
    zapros = "select m.id, u.n_name, m.date, m.text, m.status from global_message m join users u on m.id_from = u.id order by + m.id";
    zaprosMySQL(zapros);
}

void Server::zapros_from_user_list_users()//������ �� ������������ ������� �������������
{
    string log;
    log = time() + " ������ �� ������������ ������� �������������.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zaprosMySQL("select * from users");
}

void Server::zapros_from_user_list_users_from_n_name()//������ �� ������������ ������� �������������
{
    string log;
    log = time() + " ������ �� ������������ ������� ������������� �� Nickname.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zaprosMySQL("select n_name from users");
}

void Server::zapros_id_n_name_all_users()//������ id, n_name ���� �������������
{
    string log;
    log = time() + " ������ id, n_name ���� �������������.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zaprosMySQL("select id, n_name from users");
}

void Server::zapros_name_by_user_id(string mes_suf)//������ ����� �� id ������������
{
    string log;
    log = time() + " ������ ����� �� id ������������.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zapros = "select n_name from users where id = '" + mes_suf + "'";
    zaprosMySQL(zapros);
}

void Server::zapros_id_by_name_user(string mes_suf)//������ id �� ����� ������������
{
    string log;
    log = time() + "������ id �� ����� ������������.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zapros = "select id from users where n_name = '" + mes_suf + "'";
    zaprosMySQL(zapros);
}

void Server::zapros_id_by_login_user(string mes_suf)//������ id �� ������ ������������.
{
    string log;
    log = time() + "������ id �� ������ ������������.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zapros = "select id from users where login = '" + mes_suf + "';";
    zaprosMySQL(zapros);
}

void Server::zapros_status_by_id_user(string mes_suf)//������ ������� ������������ �� id
{
    string log;
    log = time() + " ������ ������� ������������ �� id.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zapros = "select status from users where id = '" + mes_suf + "';";
    zaprosMySQL(zapros);
}

void Server::zapros_status_by_n_name(string mes_suf)//������ ������� ������������ �� n_name
{
    string log;
    log = time() + " ������ ������� ������������ �� n_name.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zapros = "select status from users where n_name = '" + mes_suf + "';";
    zaprosMySQL(zapros);
}

void Server::zapros_id_from_id_to_by_personal_cor()//������ id_from, id_to �� ������ ���������
{
    string log;
    log = time() + " ������ id_from, id_to �� ������ ���������.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zapros = "select id_from, id_to from message";
    zaprosMySQL(zapros);
}

void Server::zapros_personal_cor_from_user(string mes_suf)//������ ������ ��������� �� �������������
{
    string n_name;
    for (int i = 0; i < mes_suf.size(); i++)
    {
        n_name += mes_suf[i];
    }
    reply.clear();
    string zapros = "SELECT f.n_name_from as n_name_from, '\t', t.n_name_to as n_name_to, '\t', m.date as date, '\t', m.text as text, '\n' FROM message m INNER JOIN mess_name_from f ON m.id = f.id INNER JOIN mess_name_to t ON m.id = t.id where n_name_from = '" + n_name + "' or n_name_to = '" + n_name + "' ORDER BY m.date";
    perepiska = true;
    zaprosMySQL(zapros);
}

void Server::zapros_message_status_by_id(string mes_suf)//������ ������� ��������� ����� ��������� �� id
{
    string log;
    log = time() + " ������ ������� ��������� ����� ��������� �� id.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zapros = "select status from global_message where id = '" + mes_suf + "';";
    zaprosMySQL(zapros);
}

void Server::zapros_user_status_changes_by_id(string mes_suf)//������ ����� ������� ������������ �� id.
{
    string log, status, id;
    int i;
    for (i = 1; i < sizeof(message); i++)
    {
        if (message[i] == ' ')break;
        id += message[i];
    }
    i++;
    for (i; i < sizeof(message); i++)
    {
        if (message[i] == '~')break;
        status += message[i];
    }
    log = time() + "������ ����� ������� ������������ �� id.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zapros = "update users set status = " + status + " where id = " + id + ";";
    zaprosMySQL(zapros);
}

void Server::zapros_user_status_changes_by_n_name(string mes_suf)//������ ����� ������� ������������ �� n_name.
{
    string log, status, n_name;
    int i;
    for (i = 1; i < sizeof(message); i++)
    {
        if (message[i] == ' ')break;
        n_name += message[i];
    }
    i++;
    for (i; i < sizeof(message); i++)
    {
        if (message[i] == '~')break;
        status += message[i];
    }
    log = time() + "������ ����� ������� ������������ �� n_name.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zapros = "update users set status = '" + status + "' where n_name = '" + n_name + "';";
    zaprosMySQL(zapros);
}

void Server::zapros_mess_status_changes_by_id(string mes_suf)//������ ����� ������� ��������� ����� ��������� �� id
{
    string log, status, id;
    int i;
    for (i = 1; i < sizeof(message); i++)
    {
        if (message[i] == ' ')break;
        id += message[i];
    }
    i++;
    for (i; i < sizeof(message); i++)
    {
        if (message[i] == '~')break;
        status += message[i];
    }
    log = time() + "������ ����� ������� ��������� ����� ��������� �� id.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zapros = "update global_message set status = " + status + " where id = '" + id + "'";
    zaprosMySQL(zapros);
}

void Server::zapros_add_mess_from_global_messages(string mes_suf)//������ ���������� ��������� ����� ���������
{
    string log, id, text, n_name;
    int i;
    char suf = '~';
    mes_suf.push_back(suf);
    for (i = 0; i < sizeof(mes_suf); i++)
    {
        if (mes_suf[i] == '+')break;
        n_name += mes_suf[i];
    }
    i++;
    for (i; i < mes_suf.length(); i++)
    {
        if (mes_suf[i] == '~')break;
        text += mes_suf[i];
    }
    log = time() + "������ ���������� ��������� ����� ���������.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zaprosMySQL("select id from users where n_name = '" + n_name + "'");
    id = reply;
    zapros = "insert global_message (id_from, text) value ('" + id + "', '" + text + "')";
    zaprosMySQL(zapros);
}

void Server::zapros_add_mess_from_messages(string mes_suf)//������ ���������� ��������� ������ ���������
{
    string log, id_from, id_to, text, n_name_from, n_name_to;
    int i;
    mes_suf += '~';
    for (i = 0; i < sizeof(mes_suf); i++)
    {
        if (mes_suf[i] == ' ')break;
        n_name_from += mes_suf[i];
    }
    i++;
    for (i; i < sizeof(mes_suf); i++)
    {
        if (mes_suf[i] == ' ')break;
        n_name_to += mes_suf[i];
    }
    i++;
    for (i; i < mes_suf.length(); i++)
    {
        if (mes_suf[i] == '~')break;
        text += mes_suf[i];
    }
    log = time() + "������ ���������� ��������� ������ ���������.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    zaprosMySQL("select id from users where n_name = '" + n_name_from + "'");
    id_from = reply;
    reply.clear();
    zaprosMySQL("select id from users where n_name = '" + n_name_to + "'");
    id_to = reply;
    reply.clear();
    zapros = "insert message (id_from, id_to, text) value ('" + id_from + "', '" + id_to + "', '" + text + "')";
    zaprosMySQL(zapros);
}

void Server::zapros_password_change(string mes_suf)//������ �� ����� ������
{
    string log;
    log = time() + " ������ �� ����� ������.";
    cout << log << endl;
    string zapros = "insert log (log) value ('" + log + "');";
    zaprosMySQL(zapros);
    changPassw(mes_suf);
}

