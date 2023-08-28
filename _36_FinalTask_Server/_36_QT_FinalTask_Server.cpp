#include "Server.h"
#include <filesystem>
#include <locale>
#include <iostream>
#include <Windows.h>
using namespace std;



int main()
{
	system("chcp 65001");
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	Server server;
	server.miServer();
	return 0;
}

