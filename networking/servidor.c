#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "utils.h"
#include "time.h"
#define MAX_DATA 500


int main(int argc, char *argv[]){
	if(argc < 1){
		printf("Informe a porta do servidor corretamente\n");
		exit(1);
	}
	else{
		char *port = argv[1];
		int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
	    struct addrinfo hints, *servinfo, *p;
	    struct sockaddr_storage client_addr; // connector's address information
	    socklen_t sin_size;
	    while(1){ 
		    int yes=1;
		    char s[INET6_ADDRSTRLEN];
		    int rv;
		    //hints will help getaddrinfo find the right address
		    memset(&hints, 0, sizeof hints);
		    hints.ai_family = AF_INET6; //specify ipv6 to work with both protocols
		    hints.ai_socktype = SOCK_STREAM;
		    hints.ai_flags = AI_PASSIVE; // use my IP
		    if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
		        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		        return 1;
		    }
		    // loop through all the results and bind to the first possible
		    for(p = servinfo; p != NULL; p = p->ai_next) {
		        if ((sockfd = socket(p->ai_family, p->ai_socktype,
		                p->ai_protocol)) == -1) {
		            perror("server: socket");
		            continue;
		        }
		        
		        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
		                sizeof(int)) == -1) {
		            perror("setsockopt");
		            exit(1);
		        }


		        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
		            close(sockfd);
		            perror("server: bind");
		            continue;
		        }

		        break;
		    }

		    freeaddrinfo(servinfo); 
		    if (p == NULL)  {
		        fprintf(stderr, "server: failed to bind\n");
		        exit(1);
		    }

		    if (listen(sockfd, 5) == -1) {
		        perror("listen");
		        exit(1);
		    }

		    printf("servidor: esperando por conexões...\n");
		    sin_size = sizeof client_addr;
			new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);   
	        if (new_fd == -1) {
	            perror("accept");
	        }
	        inet_ntop(client_addr.ss_family,
	            get_in_addr((struct sockaddr *)&client_addr),
	            s, sizeof s);
	        printf("servidor: conexão recebida de %s\n", s);
	        int flag=1;
	        unsigned int count_data=0;
	        time *t[MAX_DATA];
	       	while(flag==1){
		    	char buf[MAX_BUFFER];
		       	buf[0]='\0';
	            close(sockfd); 
	            int numbytes;
	            if ((numbytes=recv(new_fd, buf, MAX_BUFFER, 0)) == -1) {
	        		perror("recv");
	        		exit(1);
	    		}
	    		buf[numbytes]='\0';
			    		
	    		if(buf[0]=='D'){
	    			char buf_copy[MAX_BUFFER];
	    			buf_copy[0]='\0';
	    			strcpy(buf_copy,buf);
					printf("servidor: comando recebido %s",buf_copy);
					
					
					t[count_data] = new_time();
					string_to_time(buf_copy,t[count_data]);
					count_data++;
					qsort(t,count_data,sizeof(time*),compare_time);	    			
				}
	    		if(buf[0] == 'C'){
	    			printf("servidor: comando recebido %s",buf);
	    			int index=0;// = buf[2] -'0';
	    			char str[MAX_BUFFER];
	    			str[0]='\0';
	    			strcpy(str,&buf[2]);
	    			sscanf(str," %d",&index);
	    			if(count_data <= index-1 || index <= 0){ 
	    				if (send(new_fd, "Valor informado não existe", 100, 0) == -1)
	                		perror("send");

	    				}
	    			else{
	    				char result[MAX_BUFFER];
	    				result[0]='\0';
	    				time_to_string(t[index-1],result);
	    				if (send(new_fd, result, strlen(result)+1, 0) == -1)
	                		perror("send");

	                }

	    		}
	    		if(buf[0] == 'O'){
	    			printf("servidor: comando recebido %s",buf);
	    			int i;
	    			char num[5];
	    			num[0]='\0';
	    			sprintf(num, "%d", count_data);
	    			if (send(new_fd, num, MAX_BUFFER, 0) == -1)
	                		perror("send");
	    			for (i = 0; i < count_data; i++){
	    				char result[MAX_BUFFER];
	    				result[0]='\0';
	    				time_to_string(t[i],result);
	    				if (send(new_fd, result, MAX_BUFFER, 0) == -1)
	                		perror("send");
	    			}
	    		}
	    		if(buf[0] == 'Z'){
	    			flag=-1;
	    			printf("servidor: conexão terminada pelo cliente\n");
	    			free_data(t,count_data);
	    			
	    		}
			}
	    	close(new_fd);  
	        
		}

	    return 0;
	}
	
}	