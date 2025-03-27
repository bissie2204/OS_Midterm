#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For fork(), close()
#include <fcntl.h>   // For STDOUT_FILENO

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // If fork() fails
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(STDOUT_FILENO);  // Close the standard output (STDOUT)
        printf("This will not be printed by the child.\n");
        // After closing stdout, this printf will have no output
    } else {
        // Parent process
        printf("This will be printed by the parent.\n");
    }

    return 0;
}
