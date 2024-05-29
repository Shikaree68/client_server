
#include <mutex>
#include <fstream>


class Server {

public:
    Server(int port);

    void Run();
    void HandleClient(int client_socket_);

private:
    int port_;
    std::ofstream log_file_;
    std::mutex mtx_;
};
