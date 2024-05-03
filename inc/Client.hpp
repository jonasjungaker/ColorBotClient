#pragma once
#include <string>
#include <SFML/Network.hpp>
#include <stdexcept>

namespace Client
{
    void showHostConfigurationWindow(bool* p_open);
    void showGameWindow(bool* p_open);
    void showScriptSelectWindow(bool* p_open);

    class Connection
    {
    public:
        Connection()
                : m_hostname(0)
                , m_connected(false)
                , m_socket()
        {}
        Connection(const Connection& other) = delete;

        bool Connect(std::string hostname, std::string hostport, std::string playerName, std::string playerID)
        {
            m_hostname = sf::IpAddress::resolve(hostname).value();
            m_hostport = std::stoi(hostport);
            m_playerID = playerID;

            sf::Socket::Status returnstatus = m_socket.connect(m_hostname, m_hostport);
            if (returnstatus == sf::Socket::Status::Done)
                m_connected = true;
            return m_connected;
        }
        bool Disconnect()
        {
            m_socket.disconnect();
            return true;
        }

        void SendMessage(std::string message);
        std::string GetMessage();

        bool IsConnected() 
        {
            return m_connected;
        }
    private:
        sf::IpAddress stringToIp(std::string address);
        std::string m_playerID;
        sf::IpAddress m_hostname;
        unsigned short m_hostport;
        bool m_connected;

        sf::TcpSocket m_socket;
    };
}