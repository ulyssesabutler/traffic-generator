#include <iostream>
#include <thread>
#include <sstream>

#include "network/socket.h"
#include "network/packet.h"
#include "util/hex.h"

std::string SRC_IP = "172.24.71.241";
std::string DEST_IP = "172.24.71.213";
uint PORT = 80; // No idea why we need to send this when there's no transport layer

void send_thread(int socket_fd)
{
    char buffer[65536];

    for (int i = 9; i >= 0; i--)
    {
        int data[] = { i };
        // Create the packet
        size_t packet_size = 0;
        create_ip_packet(buffer, SRC_IP, DEST_IP, (char*) data, sizeof(data), packet_size);

        std::stringstream ss;
        ss << "Sending packet " << i << " of size " << packet_size << ": " << buffer_to_hex(buffer, packet_size);
        std::cout << ss.str() << std::endl;

        // Send the packet
        send_packet(socket_fd, (char*) buffer, packet_size, DEST_IP, PORT);
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
