#include <tcp_server.hpp>
#include <iostream>
#include <thread>
#include <array>
#include <utils.hpp>

class Server {
public:
    static constexpr int port = 550;

    Server() : serverSocket(port) {
        std::cout << "Created the server instance!" << std::endl;
        isOpen = true;
    }

    ~Server() {
        isOpen = false;
        std::cout << "Destructed server instance!" << std::endl;
    }

    void run() {
        serverSocket.Open();
        serverSocket.Bind();
        serverSocket.Listen(1);
        std::thread thread(&Server::host, this);
        thread.detach();
    }
private:
    bool isOpen = false;
    ServerSocket serverSocket;

    enum Axis{
        X,
        Y,
        Z
    };

    void host() {
        std::cout << "Server is now running on port " << port << "!" << std::endl;
        while (true) {
            ClientSocket clientSocket = serverSocket.Accept();
            clientSocket.SetTimeout(0, 500000);
            while (true) {
                clientSocket.Send(std::array<unsigned char, 1> { 1 });
                auto recv = clientSocket.Receive<1 + 12, unsigned char>();
                if (recv.has_value()) {
                    auto data = recv.value();
                    std::array<float, 3> axis;
                    axis = get_float(axis.begin() + 1, axis.end());
                    std::cout << axis[Axis::X] << ", " << axis[Axis::Y] << ", " << axis[Axis::Z] << std::endl;
                } else {
                    break;
                }
            }
            std::cout << "Lost connection!" << std::endl;
        }
    }
};