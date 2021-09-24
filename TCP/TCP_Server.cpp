#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <thread>

using namespace std;

#pragma comment(lib, "Ws2_32.lib")

const PCSTR MY_PORT = "35156";
const int BUFLEN = 1024;

void startService(SOCKET clientSocket);

int main()
{
	int iResult;

	//====Init Winsock====
	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	//====Create a Socket====
	addrinfo* result = nullptr, hints;

	ZeroMemory(&hints, sizeof(hints)); //memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_STREAM; //stream socket
	hints.ai_protocol = IPPROTO_TCP; //TCP
	hints.ai_flags = AI_PASSIVE;
	iResult = getaddrinfo(nullptr, MY_PORT, &hints, &result); //domain address -> IP address

	//create a listen socket
	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	//====Bind====
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	freeaddrinfo(result); //no longer needed

	//====Listen====
	listen(ListenSocket, SOMAXCONN);

	//====Accept====
	printf("Server is running. (Press Ctrl+C to shutdown.)\n");
	while (1)
	{
		SOCKET ClientSocket = INVALID_SOCKET;
		ClientSocket = accept(ListenSocket, nullptr, nullptr);

		printf("new connection!\n");
		thread t(startService, ClientSocket);
		t.detach();
	}

	WSACleanup();

	return 0;
}

void startService(SOCKET clientSocket)
{
	int iResult;

	//====Receive and Send====
	char buf[BUFLEN];
	int buflen = BUFLEN;
	ZeroMemory(buf, buflen);

	do
	{
		//====Recv====
		iResult = recv(clientSocket, buf, buflen, 0);
		if (iResult > 0)
		{
			printf("Bytes received: %s (%d byte)\n", buf, iResult);

			//edit recvbuf
			_strupr_s(buf, buflen); //a -> A

			//====Send====
			iResult = send(clientSocket, buf, iResult, 0);
			if (iResult == SOCKET_ERROR)
			{
				printf("send failed: %d\n", WSAGetLastError());
				break;
			}
			printf("Bytes sent    : %s (%d byte)\n", buf, iResult);
		}
		else if (iResult == 0) { printf("Connection closing...\n"); }
		else
		{
			printf("recv failed: %d\n", WSAGetLastError());
			break;
		}
	} while (iResult > 0);

	//====Disconnect the Server====
	iResult = shutdown(clientSocket, SD_SEND); //SD_SEND: no more data will be sent (send FIN packet)

	//cleanup
	closesocket(clientSocket);
}