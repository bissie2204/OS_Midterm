#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>

using namespace std;

void run_program(const char* program, int count, char mode) {
    pid_t pid;
    for (int i = 0; i < count; ++i) {
        pid = fork();  // Create a new child process

        if (pid < 0) {
            cerr << "Fork failed!" << endl;
            exit(1);
        }

        if (pid == 0) {
            // Child process
            char* const args[] = { (char*)program, nullptr };  // Program arguments
            execvp(program, args);  // Replace the child process with the program
            cerr << "Exec failed!" << endl;
            exit(1);
        } else {
            // Parent process
            if (mode == 's') {
                // If sequential, wait for the child to finish before forking the next
                waitpid(pid, nullptr, 0);
            }
        }
    }

    if (mode == 'p') {
        // If parallel, wait for all child processes to finish
        for (int i = 0; i < count; ++i) {
            waitpid(-1, nullptr, 0);  // Wait for any child process to finish
        }
    }
}

int main() {
    string program;
    int count;
    char mode;

    while (true) {
        // Prompt the user for input
        cout << "closh> ";
        getline(cin, program);  // Get the program to run

        // If the input is empty, break out of the loop
        if (program.empty()) break;

        // Get the number of copies to run
        cout << "count> ";
        cin >> count;

        // Validate the count
        if (count < 1 || count > 9) {
            cerr << "Count must be between 1 and 9!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer
            continue;
        }

        // Get the execution mode (parallel or sequential)
        cout << "[p]arallel or [s]equential> ";
        cin >> mode;
        cin.ignore();  // Clear the newline character left by the previous input

        // Validate the mode input
        if (mode != 'p' && mode != 's') {
            cerr << "Invalid mode! Use 'p' for parallel or 's' for sequential." << endl;
            continue;
        }

        // Run the program with the specified count and mode
        run_program(program.c_str(), count, mode);
    }

    return 0;
}
