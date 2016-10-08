cmake_minimum_required(VERSION 3.6)
project(NetworkProgramingLab)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(MSA

        MSA/cRoom.cpp
        MSA/cRoom.h
        MSA/LoginDispatcher.cpp
        MSA/LoginDispatcher.h
        MSA/Main.cpp
        MSA/TcpServerMessenger.cpp
        MSA/TcpServerMessenger.h
        MSA/User.cpp
        MSA/User.h
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

add_executable(MSA ${MSA})
set(MCA

        MCA/UdpClientMessenger.cpp
        MCA/UdpClientMessenger.h
        MCA/TcpCLientMessenger.cpp
        MCA/TcpCLientMessenger.h
        MCA/main.cpp
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

add_executable(MCA ${MCA})

set(TEST
        Tests/MessengerTest.cpp
        Tests/MessengerTest.h
        Tests/TCPSocketTest.cpp
        Tests/TCPSocketTest.h
        Tests/UDPSocketTest.cpp
        Tests/UDPSocketTest.h
        Tests/main.cpp
        MSA/cRoom.cpp
        MSA/cRoom.h
        MSA/LoginDispatcher.cpp
        MSA/LoginDispatcher.h
        MSA/TcpServerMessenger.cpp
        MSA/TcpServerMessenger.h
        MSA/User.cpp
        MSA/User.h
        MCA/UdpClientMessenger.cpp
        MCA/UdpClientMessenger.h
        MCA/TcpCLientMessenger.cpp
        MCA/TcpCLientMessenger.h
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