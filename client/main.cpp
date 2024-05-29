#include "client.h"

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <client name> <server port> <period in seconds>\n";
        return 1;
    }

    std::string clientName = argv[1];
    int serverPort = std::stoi(argv[2]);
    int periodSeconds = std::stoi(argv[3]);

    Client client(clientName, serverPort, periodSeconds);
    client.Run();

    return 0;
}