#include <BackEnd/ClientSocket.hpp>
#include <BackEnd/Server.hpp>
#include <Logger.hpp>
#include <thread>

static Glib::ustring get_type_name(BackEnd::Client::Type type);
static void communicate(BackEnd::Client &client);

BackEnd::Client::Client(const ClientSocket &clientSocket)
    : clientSocket(clientSocket), type(Type::None)
{
    Logger::verbose(clientSocket.ip + " -> Handshake!");
    std::thread thread(communicate, std::ref(*this));
    thread.detach();
}

BackEnd::Client::Client(const Client &client)
    : clientSocket(client.clientSocket), type(client.type)
{
}

bool BackEnd::Client::operator==(const Client &client)
{
    return this->clientSocket.ip == client.clientSocket.ip &&
           this->type == client.type;
}

BackEnd::Client &BackEnd::Client::operator=(const Client &)
{
    return *this;
}

Glib::ustring get_type_name(BackEnd::Client::Type type)
{
    switch (type)
    {
    case BackEnd::Client::Type::Satellite:
        return "Satellite";
    case BackEnd::Client::Type::Phone:
        return "Phone";
    case BackEnd::Client::Type::Compass:
        return "Compass";
    case BackEnd::Client::Type::PowerSupplies:
        return "PowerSupplies";
    case BackEnd::Client::Type::None:
        return "None";
    }
    return "Error";
}

void communicate(BackEnd::Client &client)
{
    { // Receive the client type
        constexpr int timeoutMicros = 500000;
        client.clientSocket.client_set_timeout(timeoutMicros);

        uint8_t buffer[sizeof(BackEnd::Client::Type)];
        Logger::verbose(client.clientSocket.ip + " -> Waiting for type...");
        bool failed = client.clientSocket.client_recv(buffer, sizeof(buffer)) <= 0;
        if (BackEnd::Server::is_open() && failed)
        {
            Logger::verbose(client.clientSocket.ip + " -> Failed to send type after " + std::to_string(timeoutMicros) + "μs!");
            client.clientSocket.client_close();
            Logger::verbose(client.clientSocket.ip + " -> Closed connection!");
            BackEnd::Server::close_connection_with(client);
            return;
        }

        client.type = BackEnd::Client::Type(*buffer);
        Logger::info(client.clientSocket.ip + " [" + get_type_name(client.type) + "] -> New connection!");

        client.clientSocket.client_recv(buffer, sizeof(buffer)); // dummy

        client.clientSocket.client_close();
        Logger::info(client.clientSocket.ip + " [" + get_type_name(client.type) + "] -> Closed connection!");
        BackEnd::Server::close_connection_with(client);
    }
}
