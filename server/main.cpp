#include "server.h"

#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <server port>\n";
        return 1;
    }

    int server_port = std::stoi(argv[1]);

    Server server(server_port);
    server.Run();

    return 0;
}