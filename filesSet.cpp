#include "filesSet.h"
namespace DNSfiles {
    uint8_t Read_uint8() {
        char c = getchar();
        while (c < '0' || c>'9')c = getchar();
        uint8_t r = 0;
        while (c >= '0' && c <= '9') {
            r = r * 10 + (c ^ 48);
            c = getchar();
        }
        return r;
    }
	std::vector<std::string> viewFile(const char* const FileName,bool showError) {
        std::ifstream in;
        in.open(FileName, std::ios::in);
        if (in.fail()) {
            std::ofstream out;
            out.open(FileName, std::ios::out);
            out.close();
            if(showError)printf("Fail to read \"%s\".\n", FileName);
            return std::vector<std::string>();
        }
        std::vector<std::string> ret;
        while (!in.eof()) {
            std::string s;
            in >> s;
            if(s.length()>1)ret.push_back(s);
        }
        in.close();
        return ret;
	}
    void setWeb() {
        std::vector<std::string> v=viewFile("webs.txt",0);
        std::set<std::string> st;
        for (auto& i : v)st.insert(i);
        while (1) {
            puts("\nEnter \"new\" to add a new website.\nEnter \"delete\" to delete a website.\nEnter \"clear\" to delete all websites.\nEnter \"view\" to view the website list.\nEnter \"exit\" to exit.");
            std::string op;
            char c = getchar();
            while ((c < 'a' || c>'z') && (c < 'A' || c>'Z'))c = getchar();
            while (c != '\n') {
                if (c >= 'a' && c <= 'z')op += c;
                else if (c >= 'A' && c <= 'Z')op += c - 'A' + 'a';
                c = getchar();
            }
            if (op == "exit")break;
            if (op == "clear")st.clear();
            else if(op=="new"||op=="delete"){
                puts("Please enter a website:");
                if (op == "new") {
                    std::cin >> op;
                    st.insert(op);
                }
                else{
                    std::cin >> op;
                    st.erase(op);
                }
            }
            else if (op == "view") {
                puts("List of websites:");
                for (auto& i : st)std::cout << i << '\n';
            }
            else puts("Unknown operation.");
        }
        std::ofstream out;
        out.open("webs.txt", std::ios::out);
        for (auto& s : st)out << s << '\n';
        out.close();
    }
    void setDNS() {
        std::vector<std::string> v = viewFile("DNS.txt", 0);
        std::set<std::string> st;
        for (auto& i : v)st.insert(i);
        while (1) {
            puts("\nEnter \"new\" to add a new DNS server.\nEnter \"delete\" to delete a DNS server.\nEnter \"clear\" to delete all DNS server.\nEnter \"view\" to view the DNS server list.\nEnter \"exit\" to exit.");
            std::string op;
            char c = getchar();
            while ((c < 'a' || c>'z') && (c < 'A' || c>'Z'))c = getchar();
            while (c != '\n') {
                if (c >= 'a' && c <= 'z')op += c;
                else if (c >= 'A' && c <= 'Z')op += c - 'A' + 'a';
                c = getchar();
            }
            if (op == "exit")break;
            if (op == "clear")st.clear();
            else if (op == "new" || op == "delete") {
                puts("Please enter 4 numbers less than 256 as your DNS server address:");
                uint8_t w = Read_uint8();
                uint8_t x = Read_uint8();
                uint8_t y = Read_uint8();
                uint8_t z = Read_uint8();
                if (op == "new")st.insert(std::to_string((unsigned int)w) + '.' + std::to_string((unsigned int)x) + '.' + std::to_string((unsigned int)y) + '.' + std::to_string((unsigned int)z));
                else if (op == "delete")st.erase(std::to_string((unsigned int)w) + '.' + std::to_string((unsigned int)x) + '.' + std::to_string((unsigned int)y) + '.' + std::to_string((unsigned int)z));
            }
            else if (op == "view") {
                puts("List of DNS servers:");
                for (auto& i : st)std::cout << i << '\n';
            }
            else puts("Unknown operation.");
        }
        std::ofstream out;
        out.open("DNS.txt", std::ios::out);
        for (auto& s : st)out << s << '\n';
        out.close();
    }
}