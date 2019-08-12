#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>


void error(const char* msg)
{
perror(msg);
exit(1);
}

int main(int argc,char* argv[])
{

        if(argc < 2)
                {
                fprintf(stderr,"Port no. not provided\n");

                }

        int sockfd,newsockfd,n,portno;
        struct sockaddr_in serv_addr,cli_addr;
        socklen_t clilen;
        char buffer[255];

        sockfd=socket(AF_INET ,SOCK_STREAM ,0);
        if(sockfd<0)
                {
                error("opening socket");
                }

        bzero((char*)& serv_addr,sizeof(serv_addr));
        portno=atoi(argv[1]);
        serv_addr.sin_family=AF_INET;
        serv_addr.sin_addr.s_addr=INADDR_ANY;
        serv_addr.sin_port=htons(portno);


                if(bind(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr))<0)
                {
                        error("Binding error takes place");


                }
                
        listen(sockfd,5);
        clilen=sizeof(cli_addr);


        newsockfd=accept(sockfd,(struct sockaddr*) &cli_addr,&clilen);


        while(1)
        {
                bzero(buffer,255);
                    n = read(newsockfd,buffer,255);
                if(n<0)
                        error("error in reading\n");

                printf("client:%s\n",buffer);
                bzero(buffer,255);
                fgets(buffer,255,stdin);

                n=write(newsockfd,buffer,255);
                if(n<0)
                        error("error in writing\n");
                int i=strncmp("bye",buffer,3);
                if(i==0)
                        {break;
                                }

        }
                close(newsockfd);
                close(sockfd);

        }
