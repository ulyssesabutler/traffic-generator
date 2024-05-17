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
    std::cout << "  Transmitting Interface:  " << opts.transmit_interface << std::endl;
    std::cout << "  Source IP Address:       " << opts.src_ip_addr << std::endl;
    std::cout << "  Destination IP Address:  " << opts.dest_ip_addr << std::endl;
    std::cout << "  Port:                    " << opts.port << std::endl;
}

void print_help()
{
    std::cout << "Usage" << std::endl;
    std::cout << "  -t Transmitting Interface" << std::endl;
    std::cout << "  -r Receiving Interfaces (specify one or more)" << std::endl;
    std::cout << "  -s Source IP Address" << std::endl;
    std::cout << "  -d Destination IP Address" << std::endl;
    std::cout << "  -p Port" << std::endl;
}

options get_options(int argc, char** argv)
{
    std::vector<std::string> receive_interfaces;
    std::string transmit_interface;
    std::string src_ip_addr;
    std::string dest_ip_addr;
    std::string port;

    int input;
    while ((input = getopt(argc, argv, "s:d:t:r:p:h")) != -1)
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
                transmit_interface = std::string(optarg);
                break;
            case 'r':
                receive_interfaces.emplace_back(optarg);
                break;
            case 'p':
                port = std::string(optarg);
                break;
            case 'h':
            default:
                print_help();
                exit(0);
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

    if (receive_interfaces.empty() || transmit_interface.empty())
    {
        std::cout << "Interfaces not provided" << std::endl;
        exit(-1);
    }

    return options
    {
        .receive_interfaces = std::move(receive_interfaces),
        .transmit_interface = std::move(transmit_interface),
        .src_ip_addr = std::move(src_ip_addr),
        .dest_ip_addr = std::move(dest_ip_addr),
        .port = std::stoi(port)
    };
}