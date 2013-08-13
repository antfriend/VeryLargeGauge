/*
changes in: C:\Program Files (x86)\Arduino\libraries\Ethernet

change to: Dhcp.h
#define HOST_NAME "WIZnet"
modified to
#define HOST_NAME "vlg00"

change to: Dhcp.cpp

    // OPT - host name
    buffer[16] = hostName;
    buffer[17] = strlen(HOST_NAME) + 6; // length of hostname + last 3 bytes of mac address
    strcpy((char*)&(buffer[18]), HOST_NAME);
    printByte((char*)&(buffer[24]), _dhcpMacAddr[3]);
    printByte((char*)&(buffer[26]), _dhcpMacAddr[4]);
    printByte((char*)&(buffer[28]), _dhcpMacAddr[5]);

modified to:

    // OPT - host name
    buffer[16] = hostName;
    buffer[17] = strlen(HOST_NAME) + 2;// length of hostname + last 1 byte of mac address
    strcpy((char*)&(buffer[18]), HOST_NAME);
    printByte((char*)&(buffer[22]), _dhcpMacAddr[5]);




*/
