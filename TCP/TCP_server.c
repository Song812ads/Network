#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv){
    int serverSocketfd, clientSocketfd;
    struct sockaddr_in serveradd, clientadd;
    int clientlength;
    // Socket create:
    if ((serverSocketfd = socket(AF_INET, SOCK_STREAM,0))<0){
        perror("Socket create fail");
        exit(1);
    }
    else printf("Socket: %d \n",serverSocketfd);
    bzero (&serveradd, sizeof(serveradd));
    serveradd.sin_family = AF_INET;
    serveradd.sin_port = htons ( 4444 );
    serveradd.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind (serverSocketfd, (struct sockaddr*) &serveradd, sizeof( serveradd))!=0){
        perror("Server bind fail");
        exit(1);
    }
    else printf("Binding...\n");
    if (listen(serverSocketfd,10)!=0)
    {
        perror("Server listen error");
        exit(1);
    }
    else printf("Listening...\n");
    bzero(&clientadd,sizeof(clientadd));
    if ((clientSocketfd = accept(serverSocketfd, (struct sockaddr*) &clientadd, &clientlength))==-1){
        printf("Server accept fail");
    }
    else printf("Server Accepted");

    char* msg = "Hello world";

    write(clientSocketfd,msg,strlen(msg));

    close(clientSocketfd);
    close(serverSocketfd);

}

