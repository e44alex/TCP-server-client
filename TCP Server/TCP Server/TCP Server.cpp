#pragma comment(lib, "WS2_32")
#include "stdafx.h"
#include <WS2tcpip.h>
#include <Winsock2.h>
#include <iostream>
using namespace std;

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET remote_socket;

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(54000);
	local.sin_addr.s_addr = INADDR_ANY;
	int c = bind(s, (struct sockaddr*)&local, sizeof(local));
	
	sockaddr_in remote_addr;
	int size = sizeof(remote_addr);

	char decision;

	cout << "press 'S' to start server, 'Q' to exit" << endl;

	cin >> decision;

	if (decision == 'Q' || decision == 'q' || decision == 'й' || decision == 'Й')
	{
		WSACleanup();

		cout << "Shutting down" << endl;

		return 0;
	}

	if (decision == 'S' || decision == 's' || decision == 'ы' || decision == 'Ы')
	{
		char host[NI_MAXHOST];
		char service[NI_MAXSERV];

		ZeroMemory(host, NI_MAXHOST);
		ZeroMemory(service, NI_MAXSERV);

		

		cout << "Server started" << endl;

		while (true)
		{
		
			if (listen(s, SOMAXCONN))
			{

				cout << "Error calling listen" << endl;

			}

			cout << "Waiting for connections" << endl;

			while (true)
			{

				char *buf = new char[255];
				char *res = new char[255];

				remote_socket = accept(s, (sockaddr*)&remote_addr, &size);

				if (remote_socket < 0)
				{

					cout << "cannot accept client" << endl;

				}

				else
				{

					cout << "Client connected" << endl;

					if (getnameinfo((sockaddr*)&remote_addr, sizeof(remote_addr), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
					{
						cout << host << " connected on port " << ntohs(remote_addr.sin_port) << endl;
					}

				}

				while (remote_socket > 0)
				{
					if (!recv(remote_socket, buf, strlen(buf), 0))
						break;

					printf("%s\n", buf);
					strcpy(res, buf);
					for (int i = 0; i < strlen(buf); i++)
					{
						res[i] = buf[i];
						if(i%4 == 0) res[i] = '%';
					}
					res[strlen(res)+1] = '\0';
					if (sendto(remote_socket, res, strlen(res), MSG_DONTROUTE, (sockaddr *)&remote_addr, sizeof(remote_addr)) < 0)
						cout << "error sending responce" << endl;
					else cout << "respoce " << res<< " sent" << endl;
					for (int i = 0; i < 255; i++) 
					{
						buf[i] = '\0';
						res[i] = '\0';
					}
				}
				cout << "Client disconnected" << endl;
				delete buf;
				delete res;
			}
		}
		
		closesocket(remote_socket);
	}

	
	WSACleanup();
	system("pause");

    return 0;
}

