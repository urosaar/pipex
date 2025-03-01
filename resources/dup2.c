#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int fd = open("file" , O_RDWR | O_CREAT);
    if(fd == -1)
        printf("ERROR\n");
    printf(" hello\n");
    int fd2 = dup2(fd,1);
    if(fd2 == -1)
        printf("ERROR2\n");
    printf("hello again\n");
    close(fd2);
    close(fd);
}

