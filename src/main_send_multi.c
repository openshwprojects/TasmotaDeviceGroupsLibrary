//
// Simple sender.c program for UDP
//
// Adapted from:
// http://ntrg.cs.tcd.ie/undergrad/4ba2/multicast/antony/example.html
//
// Changes:
// * Compiles for Windows as well as Linux
// * Takes the port and group on the command line
//
// Note that what this program does should be equivalent to NETCAT:
//
//     echo "Hello World" | nc -u 239.255.255.250 1900

#ifdef _WIN32
    #include <Winsock2.h> // before Windows.h, else Winsock 1 conflict
    #include <Ws2tcpip.h> // needed for ip_mreq definition for multicast
    #include <Windows.h>
#pragma comment(lib, "Ws2_32.lib")
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h> // for sleep()
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shared.h"

#include "deviceGroups_public.h"


int main(int argc, char *argv[])
{
	int nbytes;
	int channelValue;
	int seq;
    struct sockaddr_in addr;
    int fd;
	const char* group = "239.255.250.250"; 
    int port = 4447;
    // !!! If test requires, make these configurable via args
    //
    const int delay_secs = 1;

#ifdef _WIN32
    //
    // Initialize Windows Socket API with given VERSION.
    //
    WSADATA wsaData;
    if (WSAStartup(0x0101, &wsaData)) {
        perror("WSAStartup");
        return 1;
    }
#endif

    // create what looks like an ordinary UDP socket
    //
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    // set up destination address
    //
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(group);
    addr.sin_port = htons(port);

	seq = 0;
	channelValue = 0;
      // now just sendto() our destination!
    //
    while (1) {
        char ch = 0;
		byte message[512];
		int len;

		message[0] = 0;
		seq++;

		if(0) {
			len = DGR_Quick_FormatPowerState(message,sizeof(message),"test",seq, 0,channelValue, 1);
			printf("Sending POWER state %i, packet size %i\n",channelValue,len);

			channelValue = !channelValue;
		} else {
			len = DGR_Quick_FormatBrightness(message,sizeof(message),"test",seq,0, channelValue);
			printf("Sending BRIGHTNESS state %i, packet size %i\n",channelValue,len);

			channelValue += 20;
			if(channelValue >255){
				channelValue = 0;
			}

		}

        nbytes = sendto(
            fd,
            message,
            len,
            0,
            (struct sockaddr*) &addr,
            sizeof(addr)
        );
        if (nbytes < 0) {
            perror("sendto");
            return 1;
        }

     #ifdef _WIN32
          Sleep(delay_secs * 1000); // Windows Sleep is milliseconds
     #else
          sleep(delay_secs); // Unix sleep is seconds
     #endif
     }

#ifdef _WIN32
    //
    // Program never actually gets here due to infinite loop that has to be
    // canceled, but since people on the internet wind up using examples
    // they find at random in their own code it's good to show what shutting
    // down cleanly would look like.
    //
    WSACleanup();
#endif

    return 0;
}