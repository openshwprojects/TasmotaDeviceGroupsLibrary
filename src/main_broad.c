// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#ifdef WINDOWS
#include <winsock.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#endif
    
#define PORT     4447 
#define MAXLINE 1024 
    
// Driver code 
int main() { 
    int len, n; 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from server"; 
    struct sockaddr_in servaddr, cliaddr; 
	int iResult;
	WSADATA wsaData;
    char bAllow = '1';

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
        
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    iResult = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char *)&bAllow, sizeof(bAllow));
	if (iResult != 0) {
		printf("WSAStartup setsockopt: %d\n", iResult);
		return 1;
	}
        
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
        
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
//    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_addr.s_addr  = inet_addr("192.168.0.118");
    servaddr.sin_port = htons(PORT); 
        
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    printf("Server listening\n"); 
	while(1) {
		len = sizeof(cliaddr);  //len is value/result 
	    
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
					0, ( struct sockaddr *) &cliaddr, 
					&len); 
		buffer[n] = '\0'; 
		printf("Received %i bytes\n", n); 
		DGR_Parse(buffer, n);
		//sendto(sockfd, (const char *)hello, strlen(hello),  
		//    0, (const struct sockaddr *) &cliaddr, 
		//        len); 
		//printf("Hello message sent.\n");  
		//    
	}
    return 0; 
}