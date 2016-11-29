cmake_minimum_required(VERSION 3.6)
project(NetworkProgramingLab)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(Server

        Server/cRoom.cpp
        Server/cRoom.h
        Server/LoginDispatcher.cpp
        Server/LoginDispatcher.h
        Server/Main.cpp
        Server/TcpServerMessenger.cpp
        Server/TcpServerMessenger.h
        Server/User.cpp
        Server/User.h
    SocketUtils/MThread.cpp
    SocketUtils/MThread.h
    SocketUtils/MultipleTCPSocketListener.cpp
    SocketUtils/MultipleTCPSocketListener.h
    SocketUtils/TCPMessengerProtocol.h
    SocketUtils/TCPSocket.cpp
    SocketUtils/TCPSocket.h
    SocketUtils/UDPSocket.cpp
    SocketUtils/UDPSocket.h

   )

add_executable(Server ${Server})
set(Client

        Client/UdpClientMessenger.cpp
        Client/UdpClientMessenger.h
        Client/TcpCLientMessenger.cpp
        Client/TcpCLientMessenger.h
        Client/main.cpp
        SocketUtils/MThread.cpp
        SocketUtils/MThread.h
        SocketUtils/MultipleTCPSocketListener.cpp
        SocketUtils/MultipleTCPSocketListener.h
        SocketUtils/TCPMessengerProtocol.h
        SocketUtils/TCPSocket.cpp
        SocketUtils/TCPSocket.h
        SocketUtils/UDPSocket.cpp
        SocketUtils/UDPSocket.h
        )

add_executable(Client ${Client})

set(TEST
        Tests/MessengerTest.cpp
        Tests/MessengerTest.h
        Tests/TCPSocketTest.cpp
        Tests/TCPSocketTest.h
        Tests/UDPSocketTest.cpp
        Tests/UDPSocketTest.h
        Tests/main.cpp
        Server/cRoom.cpp
        Server/cRoom.h
        Server/LoginDispatcher.cpp
        Server/LoginDispatcher.h
        Server/TcpServerMessenger.cpp
        Server/TcpServerMessenger.h
        Server/User.cpp
        Server/User.h
        Client/UdpClientMessenger.cpp
        Client/UdpClientMessenger.h
        Client/TcpCLientMessenger.cpp
        Client/TcpCLientMessenger.h
        SocketUtils/MThread.cpp
        SocketUtils/MThread.h
        SocketUtils/MultipleTCPSocketListener.cpp
        SocketUtils/MultipleTCPSocketListener.h
        SocketUtils/TCPMessengerProtocol.h
        SocketUtils/TCPSocket.cpp
        SocketUtils/TCPSocket.h
        SocketUtils/UDPSocket.cpp
        SocketUtils/UDPSocket.h
        )

add_executable(TEST ${TEST})