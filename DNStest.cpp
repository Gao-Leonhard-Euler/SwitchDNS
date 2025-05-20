#include "DNStest.h"
namespace DNStest {
    const int time_limit = 1024;
    uint8_t recvData[DNStest_revSize];
    std::pair<long long,int> test_once(SOCKET& sock, const char* const dnsIP, DNS_query* QUERYs, int queryNum) {
        sockaddr_in DNSaddr;
        DNSaddr.sin_family = AF_INET;
        DNSaddr.sin_port = htons(53);
        DNSaddr.sin_addr.s_addr = inet_addr(dnsIP);
        int addrSize = sizeof(DNSaddr), fails = 0;
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < queryNum; i++) {
            if (sendto(sock, (char*)QUERYs[i].message, QUERYs[i].size, 0, (sockaddr*)&DNSaddr, addrSize) == SOCKET_ERROR)fails++;
            else{
                int rec = recvfrom(sock, (char*)recvData, DNStest_revSize, 0, (sockaddr*)&DNSaddr, &addrSize);
                while (rec != SOCKET_ERROR) {
                    if (recvData[0] == QUERYs[i].message[0] && recvData[1] == QUERYs[i].message[1])break;
                    rec = recvfrom(sock, (char*)recvData, DNStest_revSize, 0, (sockaddr*)&DNSaddr, &addrSize);
                }
                fails += (rec == SOCKET_ERROR);
            }
        }
        auto end = std::chrono::steady_clock::now();
        return std::make_pair((std::chrono::duration_cast<std::chrono::microseconds>(end - start)).count(),fails);
    }
    bool cmp(std::pair<std::string, std::pair<double, double>>  x, std::pair<std::string, std::pair<double, double>>  y) {
        return x.second.second == y.second.second ? x.second.first < y.second.first : x.second.second > y.second.second;
    }
    std::vector<std::pair<std::string, std::pair<double, double>>> tests(unsigned int times) {
        std::vector<std::string> q = DNSfiles::viewFile("webs.txt");
        srand(time(0) + rand());
        int queryNum=q.size();
        DNS_query* QUERYs = new DNS_query[queryNum];
        for (int i = 0; i < queryNum; i++) {
            int len = q[i].length() + 1, cnt = 0, pre = 0;
            char* c = new char[len + 1];
            c[len] = 0;
            for (int j = 1; j <= len; j++) {
                if (q[i][j - 1] == '.') {
                    c[pre] = cnt;
                    cnt = 0;
                    pre = j;
                }
                else {
                    c[j] = q[i][j - 1];
                    ++cnt;
                }
            }
            c[pre] = cnt - 1;
            QUERYs[i].set(rand(), c, len + 1);
            delete[] c;
        }
        q = DNSfiles::viewFile("DNS.txt");
        std::vector<std::pair<std::string, std::pair<double, double> > > ret;
        for(auto i:q)ret.push_back(std::make_pair(i,std::make_pair(0.0,(double)queryNum*times)));
        if (queryNum == 0) {
            puts("Error. No websites.");
            return ret;
        }
        WSADATA wsaData;
        while (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
            puts("WSA startup error. Enter 'Y' to retry or enter 'N' to exit.");
            char c = getch();
            while (c != 'Y' && c != 'y' && c != 'N' && c != 'n')c = getch();
            if (c == 'N' || c == 'n')exit(1);
        }
        SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        while (sock == INVALID_SOCKET) {
            wprintf(L"socket function failed with error = %d. Enter 'Y' to retry or enter 'N' to exit.\n", WSAGetLastError());
            char c = getch();
            while (c != 'Y' && c != 'y' && c != 'N' && c != 'n')c = getch();
            if (c == 'N' || c == 'n') {
                WSACleanup();
                exit(1);
            }
            sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        }
        while (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&time_limit, 4) == SOCKET_ERROR) {
            wprintf(L"set sockopt SNDTIMEO failed with error: %u. Enter 'Y' to retry or enter 'N' to exit.\n", WSAGetLastError());
            char c = getch();
            while (c != 'Y' && c != 'y' && c != 'N' && c != 'n')c = getch();
            if (c == 'N' || c == 'n') {
                WSACleanup();
                exit(1);
            }
        }
        while (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&time_limit, 4) == SOCKET_ERROR) {
            wprintf(L"set sockopt RCVTIMEO failed with error: %u. Enter 'Y' to retry or enter 'N' to exit.\n", WSAGetLastError());
            char c = getch();
            while (c != 'Y' && c != 'y' && c != 'N' && c != 'n')c = getch();
            if (c == 'N' || c == 'n') {
                WSACleanup();
                exit(1);
            }
        }
        sockaddr_in ANYaddr;
        ANYaddr.sin_family = AF_INET;
        ANYaddr.sin_port = htons(0);
        ANYaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        bind(sock, (sockaddr*)&ANYaddr, sizeof(ANYaddr));
        for (unsigned int t = 0; t < times; t++)for (auto& p : ret) {
            std::pair<long long, int> ret=test_once(sock, p.first.c_str(), QUERYs, queryNum);
            p.second.first += ret.first; p.second.second -= ret.second;
        }
        for (auto& p : ret) {
            p.second.first /= times * 1000.0 * queryNum;
            p.second.second /= times * queryNum;
        }
        closesocket(sock);
        WSACleanup();
        delete[] QUERYs;
        std::sort(ret.begin(), ret.end(), cmp);
        return ret;
    }
    std::map<std::string, std::pair<std::string, std::vector<std::string>>>  DNS_search() {
        ULONG outBufLen = 0;
        std::map<std::string, std::pair<std::string, std::vector<std::string>>>  Adapters;
        PIP_ADAPTER_ADDRESSES pAddresses = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(), 0, sizeof(IP_ADAPTER_ADDRESSES));
        if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == ERROR_BUFFER_OVERFLOW) {
            HeapFree(GetProcessHeap(), 0, pAddresses);
            pAddresses = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(), 0, outBufLen);
        }
        while (pAddresses == NULL) {
            puts("Memory allocation failed for IP_ADAPTER_ADDRESSES struct.  Enter 'Y' to retry or enter 'N' to exit.");
            char c = getchar();
            while (c != 'Y' && c != 'y' && c != 'N' && c != 'n')c = getchar();
            if (c == 'N' || c == 'n')return Adapters;
            pAddresses = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(), 0, sizeof(IP_ADAPTER_ADDRESSES));
            if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == ERROR_BUFFER_OVERFLOW) {
                HeapFree(GetProcessHeap(), 0, pAddresses);
                pAddresses = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(), 0, outBufLen);
            }
        }
        DWORD dwRetVal = GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen);
        if (dwRetVal == NO_ERROR) {
            PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses;
            while (pCurrAddresses) {
                IP_ADAPTER_DNS_SERVER_ADDRESS* pDNServer = pCurrAddresses->FirstDnsServerAddress;
                if (pDNServer && pDNServer->Address.lpSockaddr->sa_family == AF_INET) {
                    std::string name , Desc;
                    for (unsigned int i = 0; pCurrAddresses->FriendlyName[i]; i++)name += (char)pCurrAddresses->FriendlyName[i];
                    for (unsigned int i = 0; pCurrAddresses->Description[i]; i++)Desc += (char)pCurrAddresses->Description[i];
                    std::vector<std::string> DNSs;
                    while (pDNServer != NULL) {
                        DNSs.push_back(std::to_string(255&(unsigned int)pDNServer->Address.lpSockaddr->sa_data[2]) + '.' + std::to_string(255 & (unsigned int)pDNServer->Address.lpSockaddr->sa_data[3]) + '.' + std::to_string(255 & (unsigned int)pDNServer->Address.lpSockaddr->sa_data[4]) + '.' + std::to_string(255 & (unsigned int)pDNServer->Address.lpSockaddr->sa_data[5]));
                        pDNServer = pDNServer->Next;
                    }
                    Adapters[name] = std::make_pair(Desc, DNSs);
                }
                pCurrAddresses = pCurrAddresses->Next;
            }
            HeapFree(GetProcessHeap(), 0, pAddresses);
            return Adapters;
        }
        else {
            printf("Call to GetAdaptersAddresses failed with error: %d\n", dwRetVal);
            HeapFree(GetProcessHeap(), 0, pAddresses);
            return Adapters;
        }
    }
}