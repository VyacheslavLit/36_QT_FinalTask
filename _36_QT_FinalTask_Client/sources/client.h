#include "Client.h"


using namespace std;

std::string client(std::string mes_cl)
{
    //Ключевые константы
    const char SERVER_IP[] = "127.0.0.1";					// IPv4 аддрес сервера
    const short SERVER_PORT_NUM = 7777;				// порт сервера
    const short BUFF_SIZE = 1024;					// Максимальный размер передаваемых получаемых сообщений

    // Ключевые переменные для всей программы
    //int erStat;										// Для проверки ошибок в функциях сокетов

    //IP-адрес в строковом формате преобразуется в числовой формат для функций сокета. Данные находятся в "ip_to_num"
    in_addr ip_to_num;
    inet_pton(AF_INET, SERVER_IP, &ip_to_num);


    // Инициализация WinSock
    WSADATA wsData;
    //erStat =
        WSAStartup(MAKEWORD(2, 2), &wsData);
/*
    if (erStat != 0) {
        std::cout << "Error WinSock version initializaion #";
        std::cout << WSAGetLastError();
        return 0;
    }
*/
    // Инициализация Socket
    SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0);
/*
    if (ClientSock == INVALID_SOCKET) {
        cout << "Ошибка инициализации сокета # " << WSAGetLastError() << endl;
                closesocket(ClientSock);
        WSACleanup();
    }
*/
    // Установление соединения с сервером
    sockaddr_in servInfo;

    ZeroMemory(&servInfo, sizeof(servInfo));

    servInfo.sin_family = AF_INET;
    servInfo.sin_addr = ip_to_num;
    servInfo.sin_port = htons(SERVER_PORT_NUM);

    //erStat =
        connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));

/*    if (erStat != 0) {
        cout << "Не удалось подключиться к серверу. Error # " << WSAGetLastError() << endl;
            closesocket(ClientSock);
        WSACleanup();
        return 0;
    }*/


    while (true) {
        std::vector <char> servBuff(BUFF_SIZE);// Буфер для получения данных
//        short packet_size = 0;// Размер отправляемого/принимаемого пакета в байтах
        std::vector<char> clientBuff; //Буфер для отправки данных
        int i;
        for (i = 0; i < (int)mes_cl.size(); ++i)clientBuff.push_back(mes_cl[i]);
        clientBuff.push_back('~');

        //packet_size =
            send(ClientSock, clientBuff.data(), clientBuff.size(), 0);
 /*       if (packet_size == SOCKET_ERROR) {
            cout << "Не удается отправить сообщение на сервер. Error # " << WSAGetLastError() << endl;
            closesocket(ClientSock);
            WSACleanup();
            return 0;
        }*/

        //packet_size =
                recv(ClientSock, servBuff.data(), 1024, 0);
/*        if (packet_size == SOCKET_ERROR) {
            cout << "Не удается получить сообщение с сервера. Error # " << WSAGetLastError() << endl;
            closesocket(ClientSock);
            WSACleanup();
            return 0;
        }
        else
        {*/
        std::string otvet(servBuff.begin(), servBuff.end());
        closesocket(ClientSock);
        WSACleanup();
        return otvet;
        //}
    }
}
