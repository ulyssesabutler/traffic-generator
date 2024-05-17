//
// Created by uab on 5/16/24.
//

#include "options.h"

#include <iostream>
#include <unistd.h>

#include "../util/string_utils.h"

void print_options(const options& opts)
{
    std::cout << "  Receiving Interfaces:    " << vec_to_string(opts.receive_interfaces) << std::endl;
    std::cout << "  Transmitting Interfaces: " << vec_to_string(opts.transmit_interfaces) << std::endl;
    std::cout << "  Source IP Address:       " << opts.src_ip_addr << std::endl;
    std::cout << "  Destination IP Address:  " << opts.dest_ip_addr << std::endl;
    std::cout << "  Port:                    " << opts.port << std::endl;
}

options get_options(int argc, char** argv)
{
    std::vector<std::string> receive_interfaces;
    std::vector<std::string> transmit_interfaces;
    std::string src_ip_addr;
    std::string dest_ip_addr;
    std::string port;

    int input;
    while ((input = getopt(argc, argv, "s:d:t:r:p:")) != -1)
    {
        switch (input)
        {
            case 's':
                src_ip_addr = std::string(optarg);
                break;
            case 'd':
                dest_ip_addr = std::string(optarg);
                break;
            case 't':
                transmit_interfaces.emplace_back(optarg);
                break;
            case 'r':
                receive_interfaces.emplace_back(optarg);
                break;
            case 'p':
                port = std::string(optarg);
                break;
            default:
                break;
        }
    }

    if (src_ip_addr.empty() || dest_ip_addr.empty())
    {
        std::cout << "IP addresses not provided" << std::endl;
        exit(-1);
    }

    if (port.empty())
    {
        std::cout << "Port not provided" << std::endl;
        exit(-1);
    }

    if (receive_interfaces.empty() || transmit_interfaces.empty())
    {
        std::cout << "Interfaces not provided" << std::endl;
        exit(-1);
    }

    return options
    {
        .receive_interfaces = std::move(receive_interfaces),
        .transmit_interfaces = std::move(transmit_interfaces),
        .src_ip_addr = std::move(src_ip_addr),
        .dest_ip_addr = std::move(dest_ip_addr),
        .port = std::stoi(port)
    };
}