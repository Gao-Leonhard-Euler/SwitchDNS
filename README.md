# SwitchDNS : A tool to switch better DNS servers

## setup

Download `SwitchDNS_Setup.msi` and `setup.exe`. Then double click the setup.exe.

## usage

When you run this application, it will automaticlly flush DNS and test the average time interval between send DNS query and receive DNS response and successful receive rate.

Then it will print DNS address, average time interval and successful rate sort by successful rate firstly and average time interval secondly.

After thar it will scan your adapters which uses IPv4 DNS servers and print them, and then ask you to change them DNS servers.

It will print "How mush DNS servers would you wants to set?" to ask you the numbers of DNS servers you wants to set. For example, if you want set the two DNS server with the highest success rate and the fastest response speed, you can press `2`.

When it have done its works, it will print "Operations done.", then you can press any key to leave.
