void file_transfer1(char* file, char* buffer){
//     int fp = open(file, O_RDWR | O_CREAT | O_TRUNC);
//     if (fp == -1){
//         perror("Error reading file\n");
//         exit(1);
//     }
//     off_t offset = 0;
//     struct stat st;
//     long size = strlen(buffer);
//     while (offset < size){
//         ssize_t readnow = pwrite(fp, buffer + offset, 1024, offset);
//         if (readnow < 0){
//             printf("Read unsuccessful \n");
//             free(buffer);
//             close(fp);
//             exit(1);
//         }
//         offset = offset+readnow;
//     }
//     close(fp);
//     printf("File read complete \n");
// }