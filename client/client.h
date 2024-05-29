#include <string>

class Client {
public:
    Client(const std::string& name, int port, int period) 
        : clientName(name)
        , serverPort(port)
        , periodSeconds(period) 
        {}

    void Run() ;
private:
    std::string clientName;
    int serverPort;
    int periodSeconds;
};
