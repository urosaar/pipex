#include <stdio.h>
#include <unistd.h>

int main() {
    char *cmd = "/bin/ls";

    if (access(cmd, X_OK) == 0) {
        printf("Command %s is executable!\n", cmd);
    } else {
        perror("Command not found or not executable");
    }

    return 0;
}
