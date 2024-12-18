#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <string>

int main() {
	std::cout << "omg!!! server in progeeesss";

	SOCKET wsocket = 0;
	SOCKET new_wsocket = 0;
	WSADATA wsaData;
	struct sockaddr_in server{};
	int server_len = 0;
	int BUFFER_SIZE = 30720;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "omg couldnt initalise ;-; ";
	}

	wsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (wsocket == INVALID_SOCKET) {
		std::cout << "omg couldnt create sock";
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(8080);
	server_len = sizeof(server);

	if (bind(wsocket, (SOCKADDR*)&server, server_len) != 0) {
		std::cout << "binding failed ;-;";
	}

	if (listen(wsocket, 20) != 0) {
		std::cout << "cannot start listening ;-; \n";
	}
	std::cout << "\nYipee!!! Listening on 127.0.0.1:8080 \n";
	
	int bytes = 0;
	while (true) {
		new_wsocket = accept(wsocket, (SOCKADDR*)&server, &server_len);
		if (new_wsocket == INVALID_SOCKET) {
			std::cout << "cannot accept ;-;\n";
			}

			char buff[30720] = { 0 };
			bytes = recv(new_wsocket, buff, BUFFER_SIZE, 0);
			if (bytes < 0) {
				std::cout << "erm couldnt read the client request";
			}

			std::string serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
			std::string response = "<html><h2>om!!!g</h2></html>";
			serverMessage.append(std::to_string(response.size()));
			serverMessage.append("\n\n");
			serverMessage.append(response);

			int bytesSent = 0;
			int totalBytesSent = 0;
			while (totalBytesSent < serverMessage.size()) {
				bytesSent = send(new_wsocket, serverMessage.c_str(), serverMessage.size(), 0);
				if (bytesSent < 0) {
					std::cout << "couldnt send response";
				}
				totalBytesSent += bytesSent;
			}
			std::cout << "sent response to client!!!";

			closesocket(new_wsocket);
	}
	closesocket(wsocket);
	WSACleanup();

	return 0;
} 