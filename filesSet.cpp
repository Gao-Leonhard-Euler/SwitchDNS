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
        system("notepad.exe webs.txt");
    }
    void setDNS() {
        system("notepad.exe DNS.txt");
    }
}