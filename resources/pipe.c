#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd[2];
    char buffer[1];

    pipe(fd);

    write(fd[1], "Hello!", 6);
    read(fd[0], buffer, 6);

    printf("Received: %s\n", buffer); 

    return 0;
}


