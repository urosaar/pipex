
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() 
{
    // int id = fork();
    // if (id == 0)
    // {
    char *args[] = {"/bin/ls", "-l", NULL};
    char *envp[] = {NULL};
    execve("/bin/ls", args, envp);
    // }
    // else{
    perror("execve failed");
    // }
    return 1;
}