//
// Created by uab on 5/16/24.
//

#include "packet.h"

#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>

struct iphdr create_ip_header(const std::string& src_ip_addr, const std::string& dest_ip_addr, size_t data_size)
{
    struct iphdr header;

    // The fields that seem to be actually important
    header.ihl = 5;
    header.version = 4;
    header.saddr = inet_addr(src_ip_addr.c_str());
    header.daddr = inet_addr(dest_ip_addr.c_str());
    header.protocol = IPPROTO_RAW;
    header.ttl = 255;  // Time to live

    // A bit hacky, but it should be fine for now
    static uint id = 0;
    header.id = htonl(id++);

    // These are values that we're kinda just ignoring
    header.tos = 0;
    header.frag_off = 0;
    header.check = 0;

    header.tot_len = sizeof(struct iphdr) + data_size;  // Total length

    return header;
}

void create_ip_packet(char* buffer, const std::string& src_ip_addr, const std::string& dest_ip_addr, char* data, size_t data_size, size_t& packet_size)
{
    iphdr header = create_ip_header(src_ip_addr, dest_ip_addr, data_size);
    std::memcpy(buffer, &header, sizeof(header));
    std::memcpy(buffer + sizeof(header), data, data_size);
    packet_size = sizeof(header) + data_size;
}

void send_packet(int socket_fd, char* buffer, ssize_t data_size, const std::string& dest_ip_addr, uint dest_port)
{
    struct sockaddr_in dest_address;
    dest_address.sin_family = AF_INET;
    dest_address.sin_port = dest_port;
    dest_address.sin_addr.s_addr = inet_addr(dest_ip_addr.c_str());

    if (sendto(socket_fd, buffer, data_size, 0, (struct sockaddr *) &dest_address, sizeof(dest_address)) < 0)
    {
        perror("Failed to send packet");
        exit(-1);
    }
}

void receive_packet(int socket_fd, char* buffer, size_t buffer_size, ssize_t& data_size)
{
    data_size = recvfrom(socket_fd, buffer, buffer_size, 0, nullptr, nullptr);
    if (data_size < 0)
    {
        perror("Error receiving packet");
        exit(-1);
    }
}
