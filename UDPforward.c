#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {

	if (argc!= 5){
		printf("Incorrect number of arugments (requires 5).\n");
	}

	int sock = socket(PF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	server_addr.sin_port=htons(atoi(argv[2]));
	if(bind(sock,(struct sockaddr *)&server_addr,sizeof(server_addr)) == -1) {
		printf("Can't bind our address (%s:%s)\n", argv[1], argv[2]);
		exit(1);
	}

	server_addr.sin_addr.s_addr=inet_addr(argv[3]);
	server_addr.sin_port=htons(atoi(argv[4]));

	struct sockaddr_in sa;
	struct sockaddr_in da;
	da.sin_addr.s_addr=0;

	while(1){
		char buf[65505];
		int sn=sizeof(sa);
		int n=recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&sa,&sn);
		if(n<=0) continue;

		sendto(sock,buf,n,0,(struct sockaddr *)&server_addr,sizeof(server_addr));
		da=sa;
	}

}
