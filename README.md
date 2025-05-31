# SwitchDNS: A Tool to Switch to Better DNS Servers

## Project Introduction

SwitchDNS is a tool designed for Windows systems to help users automatically scan and select better DNS servers. By testing the response times and success rates of multiple DNS servers, it provides users with the best DNS server options to enhance network access speed and stability.

## Features

- **Automatic Adapter Scanning**: Automatically scans all network adapters using IPv4 DNS servers upon startup.
- **DNS Server Testing**: Supports testing the response times and success rates of multiple DNS servers.
- **Customizable Test Websites**: Users can customize the list of websites for testing to more accurately reflect actual network usage scenarios.
- **DNS Server Configuration**: One-click configuration of the selected DNS server for a specified adapter.
- **Adapter Management**: Supports viewing and managing DNS server settings for all network adapters.

## Installation and Setup

### System Requirements

Windows 7 and above, x64.

### Installation Steps

1. Download the `SwitchDNS_Setup.msi` and `setup.exe` files.
2. Double-click `setup.exe` to start the installation program.
3. Follow the installation wizard's prompts to complete the installation process.
4. After installation, launch the SwitchDNS application.

## Usage Instructions

### Launching the Application

- Upon launching the SwitchDNS application, it will automatically scan all network adapters using IPv4 DNS servers and display them in the main interface.

### Testing DNS Servers

- Click the "test DNS servers" button to start testing all DNS servers listed in the `DNS.txt` file.
- After testing, the application will display the average response time and success rate for each DNS server in the text box at the bottom of the interface.
- The test results will be automatically sorted by success rate as the primary key and average speed as the secondary key, with the best DNS server displayed at the top.

### Setting DNS Servers

- Select a network adapter and click its corresponding "set DNS" button.
- The system will automatically configure the top two DNS servers from the test results as the primary and secondary DNS servers for that adapter.

### Modifying Test Websites

- Click on "Files" -> "modify websites" in the menu bar to open the `webs.txt` file.
- Users can add or remove website addresses in this file, with one website per line.

### Modifying DNS Server List

- Click on "Files" -> "modify DNS servers" in the menu bar to open the `DNS.txt` file.
- Users can add or remove DNS server addresses in this file, with one DNS server per line.

## Copyright Notice

SwitchDNS is an open-source software licensed under the LGPL-3.0 license.
