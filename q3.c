#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For fork(), exit()

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // If fork() fails
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("hello\n");
        exit(0);  // Ensure the child process terminates before parent starts
    } else {
        // Parent process
        printf("goodbye\n");
    }

    return 0;
}
