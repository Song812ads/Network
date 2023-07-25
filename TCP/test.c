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
#define BUFFLEN 50000

int checkfile(char* buffer){
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

void file_transfer(char* buffer){
    int fp = open(buffer, O_RDONLY);
    if (fp == -1){
        perror("Error reading file\n");
        exit(1);
    }
    off_t offset = 0;
    struct stat st;
    long size;
    if (stat(buffer, &st) == 0) size = st.st_size;
    while (offset < size){
        ssize_t readnow = pread(fp, buffer+offset, 1024, offset);
        if (readnow < 0){
            printf("Read unsuccessful \n");
            free(buffer);
            close(fp);
            exit(1);
        }
        offset = offset+readnow;
    }
    close(fp);
    printf("%s",buffer);
    printf("File read complete \n");
}

void file_transfer1(char* file, char* buffer){
    int fp = open(file, O_RDWR | O_APPEND | O_CREAT | O_SYNC, 0644);
    if (fp == -1){
        perror("Error writing file\n");
        exit(1);
    }
    off_t offset = 0;
    struct stat st;
    long size = strlen(buffer);
    printf("%d",size);
    int t =0;
    while (offset < size){
        ssize_t readnow = pwrite(fp, buffer + offset, 10, offset);
        if (readnow < 0){
            printf("Read unsuccessful \n");
            free(buffer);
            close(fp);
            exit(1);
        }
        printf("%d",t++);
        offset = offset+readnow;
    }
    close(fp);
    printf("File write complete \n");
}

int main()
{
   char *buffer = (char* )malloc(BUFFLEN * sizeof(char));
    memset(buffer,'\0', BUFFLEN);
    strcpy(buffer,"text.txt");
//    const char *buffer1 = "/home/phuongnam/text.txt";
//     if (access(buffer,F_OK)==0) printf("Exist");
//     else printf("No");

    char* path = "/home/phuongnam/transmit/";
    size_t len = strlen(path);
    char* path_buffer = malloc(len+strlen(buffer));
    strcpy(path_buffer,path);
    strcpy(path_buffer+len,buffer);
    memset(buffer,'\0',BUFFLEN);
    strcpy(buffer,path_buffer);
    free(path_buffer);
    file_transfer(buffer);
    file_transfer1("text.txt",buffer);
    free(buffer);
    return 0;

}