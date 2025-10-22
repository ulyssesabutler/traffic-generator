//
// Created by uab on 5/15/24.
//

#ifndef TRAFFIC_GENERATOR_PACKET_H
#define TRAFFIC_GENERATOR_PACKET_H

#include <string>
#include <cstdint>

void create_ip_packet(char* buffer, const std::string& src_ip_addr, const std::string& dest_ip_addr, char* data, size_t data_size, size_t& packet_size);
void create_udp_packet(char* buffer, const std::string& src_ip_addr, const std::string& dest_ip_addr, uint16_t src_port, uint16_t dst_port, char* data, size_t data_size, size_t& packet_size);
void create_padded_udp_packet(char* buffer, const std::string& src_ip_addr, const std::string& dest_ip_addr, uint16_t src_port, uint16_t dst_port, const char* data, size_t data_size, size_t& packet_size);

void send_packet(int socket_fd, char* buffer, ssize_t data_size, const std::string& dest_ip_addr, uint dest_port);
void receive_packet(int socket_fd, char* buffer, size_t buffer_size, ssize_t& data_size);

#endif //TRAFFIC_GENERATOR_PACKET_H
