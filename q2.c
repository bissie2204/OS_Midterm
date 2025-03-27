#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>   // For open()
#include <unistd.h>  // For fork(), write(), close()

int main() {
    // Open a file with read & write permissions, create if it doesn't exist
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Create a new process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        write(fd, "Hello from child\n", 17);
    } else {
        // Parent process
        write(fd, "Hello from parent\n", 18);
    }

    // Close the file in both processes
    close(fd);

    return 0;
}
