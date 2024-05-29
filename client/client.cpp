#include "client.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <chrono>
#include <thread>


void Client::Run(){
    while (true) {
        int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket < 0) {
            std::cerr << "Error creating socket\n";
            return;
        }

        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "Connection failed\n";
            return;
        }

        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto time = std::chrono::system_clock::to_time_t(now);
        char timeStr[20];
        std::strftime(timeStr, 20, "%Y-%m-%d %H:%M:%S", std::localtime(&time));

        std::string message = "[" + std::string(timeStr) + "." + std::to_string(now_ms.time_since_epoch().count() % 1000) + "] " + clientName + "\n";
        send(clientSocket, message.c_str(), message.size(), 0);

        close(clientSocket);

        std::this_thread::sleep_for(std::chrono::seconds(periodSeconds));
    }
}