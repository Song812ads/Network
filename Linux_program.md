# PIPELINE - FILE I/O:

Header file :
```
#ifndef TLPI_HDR_H
#define TLPI_HDR_H /* Prevent accidental double inclusion */
#include <sys/types.h> /* Type definitions used by many programs */
#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Prototypes of commonly used library functions,
plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h> /* Prototypes for many system calls */
#include <errno.h> /* Declares errno and defines error constants */
#include <string.h> /* Commonly used string-handling functions */
#include "get_num.h" /* Declares our functions for handling numeric
arguments (getInt(), getLong()) */
#include "error_functions.h" /* Declares our error-handling functions */
typedef enum { FALSE, TRUE } Boolean;
#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))
#endif
```

Lệnh: 
```
fd = open(pathname, flags, mode) .  If the file
doesn’t exist, open() may create it

numread = read(fd, buffer, count) reads at most count bytes from the open file
referred to by fd and stores them in buffer. The read() call returns the number of
bytes actually read. If no further bytes could be read (i.e., end-of-file was
encountered), read() returns 0.

numwritten = write(fd, buffer, count) writes up to count bytes from buffer to the
open file referred to by fd. The write() call returns the number of bytes actually
written, which may be less than count.

status = close(fd) is called after all I/O has been completed, in order to release
the file descriptor fd and its associated kernel resources


```

Flag Open: 

![Alt text](image.png)

![Alt text](image-1.png)

![Alt text](image-2.png)

0_EXCL: đi chung với 0_CREAT để tạo 1 file, khi ban đầu sẽ kiểm tra xem file có tồn tại không, nếu có sẽ không cho phép mở

0_APPEND: đảm bảo wr từ điểm cuối của file tránh trường hợp nhiều ng cùng wr

0_NONBLOCK: use trong TH FIFOs, 

(part1: file access, part2: file creation, part3: open file status)

truncating to zero (nội dung file chỉ còn trên file system trong code thì k): 0_TRUNC

```
/* Open new or existing file for reading and writing, truncating to zero
bytes; file permissions read+write for owner, nothing for all others */
fd = open("myfile", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
if (fd == -1)
errExit("open");
/* Open new or existing file for writing; writes should always
append to end of file */
fd = open("w.log", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND,
S_IRUSR | S_IWUSR);
if (fd == -1)
errExit("open");
```

File descriptor: 

![Alt text](image-3.png)

Read:
```
ssize_t read(int fd, void *buffer, size_t count);
Returns number of bytes read, 0 on EOF, or –1 on error
```

Lưu ý khi read:
```
char buffer[MAX_READ + 1];
ssize_t numRead;
numRead = read(STDIN_FILENO, buffer, MAX_READ);
if (numRead == -1)
errExit("read");
buffer[numRead] = '\0';
printf("The input data was: %s\n", buffer);
Because the terminating null byte requires a byte of memory, the size of buffer must
be at least one greater than the largest string we expect to read.
```

Lseek: pointer đến vị trí trong file

![Alt text](image-4.png)
![Alt text](image-5.png)

fcntl: chỉnh sửa thay dôi mode access của file đang mở. The flags that can be modified are O_APPEND, O_NONBLOCK, O_NOATIME, O_ASYNC, and
O_DIRECT.

Quy tắc:

 Two different file descriptors that refer to the same open file description share
a file offset value. Therefore, if the file offset is changed via one file descriptor
(as a consequence of calls to read(), write(), or lseek()), this change is visible
through the other file descriptor. This applies both when the two file descrip-
tors belong to the same process and when they belong to different processes.

Similar scope rules apply when retrieving and changing the open file status
flags (e.g., O_APPEND, O_NONBLOCK, and O_ASYNC) using the fcntl() F_GETFL and F_SETFL
operations.

By contrast, the file descriptor flags (i.e., the close-on-exec flag) are private to
the process and file descriptor. Modifying these flags does not affect other file
descriptors in the same process or a different process.

Dup: lặp lại 1 file descriptor. 

VD:
```
close(2); /* Frees file descriptor 2 */
newfd = dup(1); /* Should reuse file descriptor 2 */
```

```
int dup2(int oldfd, int newfd); : đóng newfd r sẽ dup oldfd sang newfd
int dup3(int oldfd, int newfd, int flags); : thêm option so với dup2
```

Nên dùng pread, pwrite tránh race condition
```
ssize_t pread(int fd, void *buf, size_t count, off_t offset);
ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
```

Scatter Gather I/O: chuyển nhiều buffer trong 1 lần chuyển duy nhất. Lưu vào trong 1 iov

```
struct iovec {
void *iov_base; /* Start address of buffer */
size_t iov_len; /* Number of bytes to transfer to/from buffer */
};
ssize_t preadv(int fd, const struct iovec *iov, int iovcnt, off_t offset);
ssize_t pwritev(int fd, const struct iovec *iov, int iovcnt, off_t offset);
```

Truncate:
```
int truncate(const char *pathname, off_t length);
int ftruncate(int fd, off_t length); 

set the size of file to the value length
```

File tạm: 
```
int mkstemp(char* template);
```

Process ID: 
```
pid_t getpid(void); : giới hạn 32767 tới giới hạn sẽ reset.
```

# Socket:

Cấu trúc Ipv4 socket address:
![Alt text](image-6.png)

Cấu trúc 1 socket thông thường:

![Alt text](image-7.png)

