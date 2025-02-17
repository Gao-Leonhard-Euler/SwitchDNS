#pragma once
#ifndef DNStest_revSize
#define DNStest_revSize 4096
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iphlpapi.h>
#include <time.h>
#include <chrono>
#include <map>
#include <algorithm>
#include <stdlib.h>
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "ws2_32.lib")
#include "filesSet.h"
namespace DNStest {
    struct DNS_query {
        uint8_t* message;
        size_t size;
        uint16_t* ID()const { return (uint16_t*)message; }
        DNS_query() :size(0) { message = NULL; }
        DNS_query(uint16_t id, const char* const c, int len) {
            size = 16 + len;
            message = new uint8_t[size];
            memset(message, 0, size);
            *(ID()) = id;
            message[2] = 1;
            message[5] = 1;
            for (int i = 0; i < len; i++)message[12 + i] = c[i];
            message[13 + len] = 1;
            message[15 + len] = 1;
        }
        void set(uint16_t id, const char* const c, int len) {
            if (size != 0)delete[] message;
            size = 16 + len;
            message = new uint8_t[size];
            memset(message, 0, size);
            *(ID()) = id;
            message[2] = 1;
            message[5] = 1;
            for (int i = 0; i < len; i++)message[12 + i] = c[i];
            message[13 + len] = 1;
            message[15 + len] = 1;
        }
        ~DNS_query() { if (size != 0)delete[] message; }
    };
    std::pair<long long, int> test_once(SOCKET& sock, const char* const dnsIP, DNS_query* QUERYs, int queryNum);
    bool cmp(std::pair<std::string, std::pair<double, double>>  x, std::pair<std::string, std::pair<double, double>>  y);
    std::vector<std::pair<std::string, std::pair<double, double>>> tests(unsigned int times = 1);
    std::map<std::string, std::pair<std::string, std::vector<std::string>>>  DNS_search();
}
#endif