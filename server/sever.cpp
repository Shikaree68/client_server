#include "server.h"

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

Server::Server(int port) : port_(port) {
    log_file_.open("log.txt", std::ios::out | std::ios::app);
}

void Server::Run() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Error creating socket\n";
        return;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Binding failed\n";
        return;
    }

    listen(server_socket, 5);

    while (true) {
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_len);

        std::thread client_thread(&Server::HandleClient, this, client_socket);
        client_thread.detach();
    }
}

void Server::HandleClient(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1023);

    mtx_.lock();
    log_file_ << buffer;
    mtx_.unlock();

    close(client_socket);
}