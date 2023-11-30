#pragma once

#include <iostream>
#include <string.h>

#include <QtNetworkVersion>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <inaddr.h>
//#include <stdio.h>
#include <vector>
#pragma comment(lib, "Ws2_32.lib")

//using namespace std;

#define MESSAGE_LENGTH_CL 1024 //Максимальный размер буфера для данных
#define PORT_CL 7777 //будем использовать этот номер порта


std::string client(std::string message);

