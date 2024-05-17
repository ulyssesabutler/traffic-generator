//
// Created by uab on 5/16/24.
//

#include "socket.h"

#include <cstring>
#include <iostream>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>

ifreq create_interface_request(const char* interface_name)
{
    struct ifreq ifr;
    strncpy(ifr.ifr_name, interface_name, IFNAMSIZ - 1);
    return ifr;
}

void set_promiscuous_mode(int socket_fd, const char* interface_name)
{
    // Search for the interface using its name
    struct ifreq ifr = create_interface_request(interface_name);

    // Retrieve the current flags
    if (ioctl(socket_fd, SIOCGIFFLAGS, &ifr) < 0)
    {
        perror(("Failed to get flags for interface " + std::string(interface_name)).c_str());
        exit(-1);
    }

    // Set the promiscuous flag
    ifr.ifr_flags |= IFF_PROMISC;

    // Set the flags on the interface
    if (ioctl(socket_fd, SIOCSIFFLAGS, &ifr) < 0)
    {
        perror(("Failed to set flags for interface " + std::string(interface_name)).c_str());
        exit(-1);
    }
}

void bind_socket_to_interface(int socket_fd, const char* interface_name)
{
    struct ifreq ifr = create_interface_request(interface_name);

    if (setsockopt(socket_fd, SOL_SOCKET, SO_BINDTODEVICE, &ifr, sizeof(ifr)) < 0)
    {
        perror(("Failed bind socket to interface " + std::string(interface_name)).c_str());
        exit(-1);
    }
}

// Note: Doesn't seem to work with raw sockets, as raw socket mode implies IP_HDRINCL
void enable_kernel_header_creation(int socket_fd)
{
    // We want the kernel to create the header for us by telling this socket that our packet will *not* include the IP header
    int off = 0;
    if (setsockopt(socket_fd, IPPROTO_IP, IP_HDRINCL, &off, sizeof(off)) < 0)
    {
        perror("Failed enable kernel header creation");
        exit(-1);
    }
}

int create_socket(const std::string& interface_name)
{
    int socket_fd;

    // This seems to imply IP_HDRINCL, so we have to construct the IP header ourselves
    if ((socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
    {
        perror("Failed to create socket");
        exit(-1);
    }

    set_promiscuous_mode(socket_fd, interface_name.c_str());
    bind_socket_to_interface(socket_fd, interface_name.c_str());

    return socket_fd;
}
