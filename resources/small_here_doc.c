#include "unistd.h"
#include "fcntl.h"

int main()
{
    char buffer[100]; 
    int fd;

    fd = open("output", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int bytes_read = read(0, buffer, 99);
    write(fd, buffer, bytes_read);

    close(fd);
    return 0;
}