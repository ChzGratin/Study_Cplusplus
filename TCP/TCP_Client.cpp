#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define MY_PORT "35156"
#define BUFLEN 1024

int main(int argc, char* argv[])
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
	hints.ai_family = AF_UNSPEC; //unspecified (IPv4 or IPv6)
	hints.ai_socktype = SOCK_STREAM; //stream socket
	hints.ai_protocol = IPPROTO_TCP; //TCP
	iResult = getaddrinfo(argv[1], MY_PORT, &hints, &result); //argv[1] = domain address of the server

	//create a connect socket
	SOCKET ConnectSocket = INVALID_SOCKET;
	ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	//====Connect====
	iResult = connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
	freeaddrinfo(result); //no longer needed

	//====Send and Receive====
	char buf[BUFLEN] = {}; //nullify
	int buflen = BUFLEN;

	printf("Input lowercase sentence: ");
	gets_s(buf, buflen);

	//====Send====
	iResult = send(ConnectSocket, buf, (int)strlen(buf), 0);
	if (iResult == SOCKET_ERROR)
	{
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	printf("Bytes sent    : %s (%d byte)\n", buf, iResult);

	iResult = shutdown(ConnectSocket, SD_SEND); //SD_SEND: no more data will be sent

	//====Receive====
	do
	{
		iResult = recv(ConnectSocket, buf, buflen, 0);
		if (iResult > 0) { printf("Bytes received: %s (%d byte)\n", buf, iResult); }
		else if (iResult == 0) { printf("Connection closed\n"); }
		else { printf("recv failed: %d\n", WSAGetLastError()); }
	} while (iResult > 0);

	//====Disconnect the Client====
	iResult = shutdown(ConnectSocket, SD_SEND); //SD_SEND: no more data will be sent (send FIN packet)

	//cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
}