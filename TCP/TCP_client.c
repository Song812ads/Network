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

void file_transfer(char* file, char* buffer){
    FILE *fp = fopen(file, "w+");
    if (fp == NULL){
        perror("Error reading file\n");
        exit(1);
    }
    long offset = 0;
    long size = strlen(buffer);
    printf("Size of file: %ld\n",size);
    while (offset < size){
        size_t readnow = fwrite(buffer, 1, size, fp);
        if (readnow < 0){
            printf("Write unsuccessful \n");
            free(buffer);
            fclose(fp);
            exit(1);
        }
        offset = offset+readnow;
    }
    fclose(fp);
    printf("File write complete \n");
}

int main(int argc, char **argv){
    signal(SIGPIPE,pipebroke);
    signal(SIGINT,exithandler);
    int socketfd; 
    struct sockaddr_in serveradd;
    unsigned char *buffer = (unsigned char* )malloc(BUFFLEN * sizeof(unsigned char));
    
    if (argc!=4){
        printf("Wrong type <server addresss> <server port>\n");
        exit(1);
    }

    // Socket create:
    if ((socketfd = socket(AF_INET, SOCK_STREAM,0))<0){
        perror("Socket create fail\n");
        exit(1);
    }
    else printf("Socket: %d \n",socketfd);

    bzero (&serveradd, sizeof(serveradd));
    serveradd.sin_family = AF_INET;
    char* port = argv[2];
    serveradd.sin_port = htons ( atoi(port) );
    if (inet_pton (AF_INET, argv[1], &serveradd.sin_addr) <= 0) {
        perror("Convert binary fail"); 
        close(socketfd);
        exit(1);
    }

    if (connect(socketfd,(struct sockaddr *)&serveradd, sizeof(serveradd))<0){
        perror("Connection fail");
        close(socketfd);
        exit(1);
    }

    memset(buffer,'\0',BUFFLEN);                   
    strcpy(buffer,argv[3]);
    if(send(socketfd,buffer,BUFFLEN,0)<0)              
    {
        printf("sending the file name to the server side failed\n");
        perror("send failed");
        exit(1);
    }
    
    memset(buffer,'\0',BUFFLEN);                   
    if(recv(socketfd,buffer,BUFFLEN,0)<0)
    {
        perror("Checkin failed");
        exit(1);
    }

    if (strcmp(buffer,"Success")==0){
        printf("%s ready to download \n",argv[3]);
        memset(buffer,'\0',BUFFLEN);                   
        strcpy(buffer,"Ready");
        if (send(socketfd,buffer,BUFFLEN,0)<0){
            printf("Fail to send success read file signal");  
            free(buffer);
            exit(1);
        }
    memset(buffer,'\0',BUFFLEN); 
    if(recv(socketfd,buffer,BUFFLEN,0)<0)
    {
        perror("Buffer read failed");
        exit(1);
    }
        file_transfer(argv[3],buffer);

    }
    else if (strcmp(buffer,"Error")==0){
        printf("%s download fail \n",argv[3]);
        exit(1);
    }

    free(buffer);
    close(socketfd);
    return 0;
}