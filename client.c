#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>      // for perror
#include <fcntl.h>      // for open
#include <unistd.h>     // for close
#include <netinet/in.h>
#include <arpa/inet.h>
int main(int argc, char *argv[])
{	
	int sockfd=0;
	int bytesRecieved=0;
    if (argc < 3)
    { // using command line argument
        printf("Usage: %s <serv_ip> <serv_port>\n", argv[0]);
        exit(1);
    }
    unsigned int len = sizeof(struct sockaddr_in);
    int cfd, serv_port;
    
    serv_port = strtoul(argv[2], NULL, 10); //string to unsigned long atoi can also be used

    

    struct sockaddr_in saddr = {0};
    saddr.sin_family = AF_INET;                 // set to AF_INET
    saddr.sin_port = htons(serv_port);          // Port number
    saddr.sin_addr.s_addr = inet_addr(argv[1]); // IP address eg "192.168.1.1"
    if ((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        exit(2);
    }
    if (connect(cfd, (struct sockaddr *) &saddr, len) < 0) {
        perror("connect");
        close(cfd);
        exit(3);
    }
while(1){
        char buf[64] = {0};
        char data[64]={0};
        
    //printf("To Send: ");
    
    //fgets(data,sizeof(data),stdin);
	FILE *fp;
 	char ch;
	fp = fopen("one.txt", "r");
 
 	if(NULL == fp)
	{
    printf("Error opening file");
	return 1;
	}
    
 	while (bytesRecieved == read(sockfd, buf, 256) > 0) {
        printf("Bytes recieved %d\n",buf);
		fwrite(buf, 1,buf,fp);
        exit(5);
    }
    
    if (recv(cfd, buf, sizeof(buf), 0) < 0) {
        perror("recv");
        exit(5);
    }
    
    printf("Server says:  %s", buf);
     
}
close(cfd);
    
    return 0;
}
