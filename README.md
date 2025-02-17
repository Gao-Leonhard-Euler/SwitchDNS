# SwitchDNS : A tool to switch better DNS servers

## setup

Download `SwitchDNS_Setup.msi` and `setup.exe`. Then double click the setup.exe.

## usage

When you run this application, it will automaticlly scan your adapters and keep that which use IPv4 DNS server.

It can scan your adapters using IPv4 DNS server and help to select better IPv4 DNS server.

When you enter `adapters`, it will print your adapters' names, descriptions and IPv4 DNS server address at last scan. You can enter `rescan` to re-scan your adapters.

When you enter `setDNS`, it will test the average time interval between send DNS query and receive DNS response and successful receive rate. Then it will print DNS address, average time interval and successful rate sort by successful rate firstly and average time interval secondly. Then you can enter the name of your adapters to select better DNS server address for them.

You can enter `modifyWEB` to view and modify the websites used to test DNS servers and enter `modifyDNS` to view and modify the DNS servers address for choice.

Enter `exit` to exit.

This application can be used in Windows system only.
