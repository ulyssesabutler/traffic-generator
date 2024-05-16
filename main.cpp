#include <iostream>
#include <thread>
#include <sstream>

#include "network/socket.h"
#include "util/hex.h"

void send_thread(int socket_fd)
{
    std::string ip_addr = "172.24.71.241";
    uint port = 80;

    for (int i = 9; i >= 0; i--)
    {
        int buffer[] = { i };
        std::stringstream ss;
        ss << "Sending packet " << i;
        std::cout << ss.str() << std::endl;

        send_packet(socket_fd, (char*) buffer, sizeof(buffer), ip_addr, port);
    }
}

[[noreturn]] void receive_thread(int socket_fd)
{
    char buffer[65536];

    while (true)
    {
        ssize_t data_size;
        receive_packet(socket_fd, buffer, sizeof(buffer), data_size);

        std::cout << "Received " << data_size << " bytes of data: " << buffer_to_hex(buffer, data_size) << std::endl;
    }
}

int main(int argc, char** argv)
{
    std::string interface_name = argv[1];

    int socket_fd = create_socket(interface_name);

    std::cout << "Starting receiver thread" << std::endl;
    std::thread receiver(receive_thread, socket_fd);

    std::cout << "Starting sender thread" << std::endl;
    std::thread sender(send_thread, socket_fd);

    receiver.join();
    sender.join();

    return 0;
}
