//headers
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"


int main(int argc, char *argv[]){
	if(argc < 2){
		fprintf(stderr,"uso: cliente <ip/nome> <porta>\n");
		exit(1);
	}
	else{
		//get server address and port number
		char *server= argv[1];
		char *port = argv[2];
		int sockfd, numbytes;  
	    struct addrinfo hints, *servinfo, *p;
	    int rv;
	    char s[INET6_ADDRSTRLEN];
	    //hints will help getaddrinfo find the right address
	    memset(&hints, 0, sizeof hints);
	    hints.ai_family = AF_UNSPEC; //work with both ipv4 and ipv6
	    hints.ai_socktype = SOCK_STREAM;

	    if ((rv = getaddrinfo(server, port, &hints, &servinfo)) != 0) {
	        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
	        return 1;
	    }

	    // loop through all the results and connect to the first possible
	    for(p = servinfo; p != NULL; p = p->ai_next) {
	        if ((sockfd = socket(p->ai_family, p->ai_socktype,
	                p->ai_protocol)) == -1) {
	            perror("cliente: socket");
	            continue;
	        }

	        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
	            close(sockfd);
	            perror("cliente: connect");
	            continue;
	        }

	        break;
	    }

	    if (p == NULL) {
	        fprintf(stderr, "cliente: falha na conexao\n");
	        return 2;
	    }

	    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
	            s, sizeof s);
	    printf("cliente: conectado a %s\n", s);
	    freeaddrinfo(servinfo); 
	    //run until get a Z command
	    while(1){
	    	char buf[MAX_BUFFER];
	    	fgets(buf, MAX_BUFFER, stdin);
	    	if(buf[0] == 'Z'){
	    		if((send(sockfd, buf, strlen(buf)+1, 0)) == -1){
	    			perror("send");
	    		}
	    		close(sockfd);
	    		printf("cliente: Conexao terminada\n");
	    		break;
	    	}
	    	else if(buf[0] == 'C') {
	    		int bytes_sent;
	    		if((bytes_sent = send(sockfd, buf, strlen(buf)+1, 0)) == -1){
	    			perror("send");
	    			exit(1);
	    		}
	    		if ((numbytes = recv(sockfd, buf, MAX_BUFFER, 0)) == -1) {
	        		perror("recv");
	        		exit(1);
	    		}

	    		buf[numbytes] = '\0';

	    		printf("%s\n",buf);

	    	}
	    	else if(buf[0] == 'D') {
	    		int bytes_sent;
	    		if((bytes_sent = send(sockfd, buf, strlen(buf)+1, 0)) == -1){
	    			perror("send");
	    			exit(1);
	    		}
	    	}
	    	else if(buf[0] == 'O'){
	    		if((send(sockfd, buf, strlen(buf)+1, 0)) == -1){
	    			perror("send");
	    			exit(1);
	    		}
	    		//receive number of data stored in the server
	    		if ((recv(sockfd, buf, MAX_BUFFER, 0)) == -1) {
	        		perror("recv");
	        		exit(1);
	    		}
	    		int n =atoi(buf);
	    		int i;
	    		//receive all data stored in the server and print it in the screen
	    		for(i=0; i < n; i++){
	    			char auxbuf[MAX_BUFFER];
	    			auxbuf[0]='\0';
	    			int nbytes;
	    			if ((nbytes=recv(sockfd, auxbuf, MAX_BUFFER, MSG_WAITALL)) == -1) {
	        			perror("recv");
	        			exit(1);
	    			}
	    			auxbuf[nbytes]='\0';

	    			printf("%s\n",auxbuf );
	    		}
	    	}
	    }
	    	close(sockfd);
	}
	return 0;
}