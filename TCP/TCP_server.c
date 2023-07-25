#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#define BUFFLEN 5000

void pipebroke()
{
    printf("\nBroken pipe: write to pipe with no readers\n");
}

void exithandler()
{
    printf("\nExiting....\n");
    exit(EXIT_FAILURE);
}

void file_transfer(char* buffer){
    int fp = open(buffer, O_RDONLY );
    if (fp == -1){
        perror("Error reading file");
        exit(1);
    }
    off_t offset = 0;
    struct stat st;
    long size;
    if (stat(buffer, &st) == 0) size = st.st_size;
    while (offset < size){
        ssize_t readnow = pread(fp, buffer + offset, 1024, offset);
        if (readnow < 0){
            printf("Read unsuccessful \n");
            free(buffer);
            close(fp);
            exit(1);
        }
        offset = offset+readnow;
    }
    close(fp);
    printf("Socket read complete ready to send \n");
}

int checkfile(unsigned char* buffer){
    if (access(buffer, F_OK) == -1){
        printf("File don't exist\n");
        return 0;
    }
    else if (access(buffer,R_OK) == -1){
        printf("Cant read file\n");
        return 0;
    }
    else {
        printf("File prepare to read\n");
        return 1;
    }
}

int main(int argc, char **argv){
    signal(SIGPIPE,pipebroke);
    signal(SIGINT,exithandler);
    int serverSocketfd, clientSocketfd, valread;
    struct sockaddr_in serveradd, clientadd;
    char *buffer = (char* )malloc(BUFFLEN * sizeof(char));
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
        close(serverSocketfd);
        exit(1);
    }
    else printf("Binding...\n");
    if (listen(serverSocketfd,10)!=0)
    {
        perror("Server listen error");
        close(serverSocketfd);
        exit(1);
    }
    else printf("Listening...\n");
    bzero(&clientadd,sizeof(clientadd));
    if ((clientSocketfd = accept(serverSocketfd, (struct sockaddr*) &clientadd, &clientlength))==-1){
        printf("Server accept fail");
        exit(1);
    }
    else printf("Server Accepted\n");

    memset(buffer,'\0', BUFFLEN);
    if (valread=recv(clientSocketfd,buffer,BUFFLEN,0)<0){
        printf("Receive error");
        memset(buffer,'\0', BUFFLEN);
        strcpy(buffer,"Error");
        if (send(clientSocketfd,buffer,BUFFLEN,0)<0){
            printf("Fail to send receive signal");
            free(buffer);
            exit(1);
        }}
    printf("Buffer: %s\n",buffer);
    char* path = "/home/phuongnam/transmit/";
    size_t len = strlen(path);
    char* path_buffer = malloc(len+strlen(buffer));
    strcpy(path_buffer,path);
    strcpy(path_buffer+len,buffer);
    memset(buffer,'\0',BUFFLEN);
    strcpy(buffer,path_buffer);
    free(path_buffer);
    if (!checkfile(buffer)){
        printf("Error access file\n");
        memset(buffer,'\0', BUFFLEN);
        strcpy(buffer,"Error");
        if (send(clientSocketfd,buffer,BUFFLEN,0)<0){
            printf("Fail to send access error signal");
            free(buffer);
            exit(1); 
    }}

    else {
        char* msg = "Success";
        if (send(clientSocketfd,msg,strlen(msg),0)<0){
            printf("Fail to send success read file signal");  
            free(buffer);
            exit(1);
        }
        char buf[128];
        if(recv(clientSocketfd,buf,128,0)<0)
    {
        printf(" Knowing the status of the file on server side failed\n");
        perror("recv failed");
        exit(1);
    }
        if (strcmp(buf,"Ready")==0){
        file_transfer(buffer);
        if (send(clientSocketfd,buffer,strlen(buffer),0)<0){
            printf("Fail to send file read");  
            free(buffer);
            exit(1);
        }}}
    free(buffer);
    close(clientSocketfd);
    close(serverSocketfd);

}