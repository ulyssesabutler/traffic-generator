//
// Created by uab on 5/15/24.
//

#ifndef TRAFFIC_GENERATOR_SOCKET_H
#define TRAFFIC_GENERATOR_SOCKET_H

#include <string>

int create_transmit_socket(const std::string& interface_name);
int create_receive_socket(const std::string& interface_name);

#endif //TRAFFIC_GENERATOR_SOCKET_H
