#include "DNStest.h"
std::map<std::string,std::pair<std::string, std::vector<std::string>>> Ads;
void Show_Adapters() {
    Ads = DNStest::DNS_search();
    printf("Amount of your adapters using IPv4 DNS server:%lld\nYour Adapters:\n", Ads.size());
    for (auto &i : Ads) {
        printf(("\n\tName: " + i.first + "\n\tDescription: " + i.second.first + "\n\tAmount of DNS servers: %lld\n").c_str(), i.second.second.size());
        for (auto& j : i.second.second) {
            puts(("\t\t" + j).c_str());
        }
    }
    puts("\nDisplay adapters done.\n");
}
int main() {
    puts("Automatically scanning your adapters...");
    Ads = DNStest::DNS_search();
    puts("Adapters scan done\n");
    while (1) {
        puts("\nEnter \"adapters\"to view your adapters using IPv4 DNS server.\nEnter \"setDNS\" to test DNS response speed and switch DNS.\nEnter \"modifyWEB\" to modify the websites used to test.\nEnter \"modifyDNS\" to modify the DNS servers address to choose.\nEnter \"exit\" to exit.");
        std::string op;
        char c = getchar();
        while ((c < 'a' || c>'z') && (c < 'A' && c>'Z'))c = getchar();
        while (c!='\n') {
            if (c >= 'a' && c <= 'z')op += c;
            else if (c >= 'A' && c <= 'Z')op += c - 'A' + 'a';
            c = getchar();
        }
        if (op == "exit")break;
        if (op == "adapters")Show_Adapters();
        else if (op == "setdns") {
            puts("Testing DNS response speed...");
            std::vector<std::pair<std::string, std::pair<double, double> > > ans = DNStest::tests(1);
            puts("DNS response speed test done.\n");
            if (ans.empty()) {
                puts("Error. There is no DNS servers.\n");
                continue;
            }
            for (auto i : ans)std::cout << i.first << "\naverage time:" << i.second.first << "ms, success rate:" << i.second.second * 100 << "%\n\n";
            while (1) {
                puts("Enter the name of adapter you wants to set, or enter a inexistent name to exit.");
                char c = getchar();
                std::string name;
                while (c != '\n') {
                    name += c;
                    c = getchar();
                }
                if (Ads.find(name) == Ads.end()) {
                    puts("Exit.\n");
                    break;
                }
                else {
                    puts("How mush DNS servers would you wants to set?");
                    unsigned int n;
                    scanf("%u", &n);
                    n = min(ans.size(), max(1, n));
                    puts("Setting DNS servers...");
                    system(((std::string)("netsh interface ip set dns \"") + name + (std::string)("\" static ") + ans[0].first).c_str());
                    for (unsigned int i = 1; i < n; i++)system(("netsh interface ip add dns \"" + name + "\" " + ans[i].first).c_str());
                    puts("DNS servers setting done.\n");
                }
            }
        }
        else if (op == "modifyweb")DNSfiles::setWeb();
        else if (op == "modifydns")DNSfiles::setDNS();
        else puts("Unknown operation.");
    }
    return 0;
}