#include "stdafx.h"
#include <winsock2.h>
#include <iostream>
#include <Ws2tcpip.h>
using namespace std;

int main()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	WSAStartup(wVersionRequested, &wsaData);

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s == INVALID_SOCKET)
	{

		cout << "Error calling socket" << endl;
		system("pause");
		return 0;
	}

	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(54000);
	inet_pton(AF_INET,"127.0.0.1", &peer.sin_addr);

	int result = connect(s, (sockaddr*) &peer, sizeof(peer));

	if(result == SOCKET_ERROR)
	{

		cout << "error calling connect. error #"<< WSAGetLastError() << endl;
		system("pause");
		closesocket(s);
		WSACleanup();

		return 0;

	}
	else 
	{
		cout << "connected local server" << endl;
	}
	
	char *buf = new char[255];
	char *res = new char[255];
	char *a = new char[255];
	cout << "Enter smtng: ";
	cin >> buf;
	send(s, buf, strlen(buf) + 1, 0);
	if (recv(s, res, strlen(res), 0))
	{
		cout << "Server reaction: ";
		for (int i = 0; res[i]>0; i++)
		{
			cout << res[i];
		}
		cout << endl;
	}
	
	char c1;
	system("pause");

	closesocket(s);
	delete buf;
	delete res;
	WSACleanup();
	return 0;
}