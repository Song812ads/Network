#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#define BUFFLEN 100

void file_transfer(char* buffer){
    

    fp = fopen(buffer,"r");
    if (fp == NULL){
        perror("Error reading file)");
        exit(1);
    }

}

int checkfile(char* buffer){
    if (access(buffer, F_OK) == -1){
        printf("File don't exist");
        return 0;
    }
    else if (access(buffer,R_OK) == -1){
        printf("Cant read file");
        return 0;
    }
    else {
        printf("File prepare to read");
        return 1;
    }
}

int main(int argc, char **argv){
    int serverSocketfd, clientSocketfd, valread;
    struct sockaddr_in serveradd, clientadd;
    char buffer[100];
    int clientlength = sizeof(clientadd);

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
            exit(1)
        }
        else printf("Server Accepted");

        memset(&buffer,'\0', BUFFLEN);
        strcmp(buffer,"Welcome!!!!");
        if (send(clientSocketfd,buffer,BUFFLEN,0)<0){
            printf("Fail to send welcome signal");
            exit(1);
        }

        memset(&buffer,'\0', BUFFLEN);
        if (valread=recv(clientSocketfd,buffer,BUFFLEN,0)<0){
            printf("Server receive fail");
            exit(1);
        }

        if (strcmp(buffer,"text.txt") == 0){
            printf("File client request not match");
            exit(1);
        }

        if (!checkfile(buffer)){
            printf("Error access file");
            memset(&buffer,'\0', BUFFLEN);
            strcmp(buffer,"Server cannot access file");
            if (send(clientSocketfd,buffer,BUFFLEN,0)<0){
                printf("Fail to send access error signal");
            exit(1);
        }       

        else {
            memset(&buffer,'\0', BUFFLEN);
            strcpy(buffer,"Read file success. File prepare to download!");
            if (send(clientSocketfd,buffer,BUFFLEN,0)<0){
                printf("Fail to send success read file");
            }
            file_transfer(buffer);
        }
    }

    close(clientSocketfd);
    close(serverSocketfd);

}