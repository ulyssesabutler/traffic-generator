#include <iostream>
#include <thread>
#include <sstream>

#include "network/socket.h"
#include "network/packet.h"
#include "util/hex.h"
#include "util/options.h"

void transmit_thread(int socket_fd, const std::string interface_name, const std::string& src_ip, const std::string& dest_ip, uint port)
{
    char buffer[65536];

    for (int i = 9; i >= 0; i--)
    {
        int data[] = { i };
        // Create the packet
        size_t packet_size = 0;
        create_padded_udp_packet(buffer, src_ip, dest_ip, port, port, (char*) data, sizeof(data), packet_size);

        std::cout << interface_name << ": "
            << "Sending packet " << i << ", " << packet_size << " bytes of data: "
            << buffer_to_hex(buffer, packet_size) << std::endl;

        // Send the packet
        //send_packet(socket_fd, buffer, packet_size, dest_ip, port);
    }
}

[[noreturn]] void receive_thread(int socket_fd, const std::string& interface_name)
{
    char buffer[65536];

    while (true)
    {
        ssize_t data_size;
        receive_packet(socket_fd, buffer, sizeof(buffer), data_size);

        std::cout << interface_name << ": "
            << "Received " << data_size << " bytes of data: "
            << buffer_to_hex(buffer, data_size) << std::endl;
    }
}

int main(int argc, char** argv)
{
    options options = get_options(argc, argv);
    std::cout << "Using parameters..." << std::endl;
    print_options(options);

    std::cout << "Starting receiver threads" << std::endl;
    std::vector<std::thread> receivers;
    for (const std::string& interface_name: options.receive_interfaces)
    {
        std::cout << "  Creating receiver for " << interface_name << std::endl;
        //receivers.emplace_back(receive_thread, create_receive_socket(interface_name), interface_name);
        std::cout << "    Done" << std::endl;
    }

    std::cout << "Starting transmit thread" << std::endl;
    std::string interface_name = options.transmit_interface;
    std::cout << "  Creating transmitter for " << interface_name << std::endl;
    std::thread transmitter
    (
        transmit_thread,
        0, //create_transmit_socket(interface_name),
        interface_name,
        options.src_ip_addr,
        options.dest_ip_addr,
        options.port
    );
    std::cout << "    Done" << std::endl;

    for (std::thread& receiver: receivers) receiver.join();
    transmitter.join();

    return 0;
}
