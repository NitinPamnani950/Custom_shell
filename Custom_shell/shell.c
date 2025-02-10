#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>

#define MAX_ARG_SIZE 100
#define MAX_INPUT_SIZE 1024

void handleBuiltInCommands(char **args);
void visualizeProcessTree();  
void executeCommand(char **args);
void redirectIO(char **args, int *input_redirect, int *output_redirect);
void parseInput(char *args[], int *arg_count, char *input);
long long compute_factorial(int x) {
    long long result = 1;
    if(x == 0){
        return 1;
    }
    do{
        result *= x;
        x--;
    }while (x > 0);
    return result;
}
int main() {
    int arg_count;
    char *args[MAX_ARG_SIZE];
    char input[MAX_INPUT_SIZE];

    while (!0) {
        printf("Custom-Shell$ ");
        fflush(stdout);

        if (fgets(input, MAX_INPUT_SIZE, stdin)) {
            input[strcspn(input, "\n")] = 0;

            if (!(strlen(input) != 0)) continue;
            else{
                parseInput(args, &arg_count, input);

                if (strcmp(args[0], "exit")) handleBuiltInCommands(args);
                else break;
            }
        }
        else{
            perror("fgets error");
            exit(EXIT_FAILURE);
            
        }
    }

    printf("Quit custom shell!!!!!!!!!!");
    printf("\n");
    return 0;
}

// Function to parse input into arguments
void parseInput(char *args[], int *arg_count, char *input) {
    int count = 0;
    char *current = input;
    char *next_space;

    while ((next_space = strchr(current, ' ')) != NULL) {
        *next_space = '\0'; // Replace space with null terminator
        args[count++] = current; // Store the current argument
        current = next_space + 1; // Move to the next token
    }

    if (*current != '\0') { // Add the last argument if it exists
        args[count++] = current;
    }

    args[count] = NULL; // Null-terminate the array
    *arg_count = count; // Set the argument count
}


// Function to handle I/O redirection
void redirectIO(char **args, int *input_redirect, int *output_redirect) {
    int input_fd = -1, output_fd = -1;
    int i = 0;

    // Handle input redirection (<)
    while (args[i] != NULL) {
        if (strcmp(args[i], "<") == 0) {
            if (!(args[i + 1] != NULL)) {
                fprintf(stderr, "Error: Missing file after '<'\n");
                return;
            }
            *input_redirect = 1;
            int temp = i+1;
            input_fd = open(args[temp], O_RDONLY);
            if (!(input_fd != -1)) {
                perror("Error opening input file");
                exit(EXIT_FAILURE);
            }
            dup2(input_fd, STDIN_FILENO); // Redirect standard input
            close(input_fd);
            args[i] = NULL; // Remove redirection operator
            break;
        }
        i++;
    }

    // Reset index for output redirection check
    i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], ">") == 0) {
            if (!(args[i + 1] != NULL)) {
                fprintf(stderr, "Error: Missing file after '>'\n");
                return;
            }
            *output_redirect = 1;
            int temp = i+1;
            output_fd = open(args[temp], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (!(output_fd != -1)) {
                perror("Error opening output file");
                exit(EXIT_FAILURE);
            }
            dup2(output_fd, STDOUT_FILENO); // Redirect standard output
            close(output_fd);
            args[i] = NULL; // Remove redirection operator
            break;
        }
        i++;
    }

    // Reset index for append redirection check
    i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], ">>") == 0) {
            if (!(args[i + 1] != NULL)) {
                fprintf(stderr, "Error: Missing file after '>>'\n");
                return;
            }
            *output_redirect = 1;
            int temp = i+1;
            output_fd = open(args[temp], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (!(output_fd != -1)) {
                perror("Error opening file for append");
                exit(EXIT_FAILURE);
            }
            dup2(output_fd, STDOUT_FILENO); // Redirect standard output for appending
            close(output_fd);
            args[i] = NULL; // Remove redirection operator
            break;
        }
        i++;
    }

    // Notify about dual redirection detection
    if (*output_redirect && *input_redirect) {
        // printf("Both input and output redirection are being used\n");
    }
}


// Function to execute non-built-in commands
void executeCommand(char **args) {
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Error: Unable to create process");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        int has_input_redirect = 0, has_output_redirect = 0;
        redirectIO(args, &has_input_redirect, &has_output_redirect);
        if (execvp(args[0], args) == -1) {
            perror("Error: Command execution failed");
            exit(EXIT_FAILURE);
        }
    } else {
        int child_status;
        if (waitpid(child_pid, &child_status, 0) == -1) {
            perror("Error: Failed to wait for child process");
        }
    }
}


// Function to handle built-in commands (cd, ls, help, exit)
void handleBuiltInCommands(char **args) {
    if (!(strcmp(args[0], "cd") != 0)) {
        if (!(args[1] != NULL)) {
            fprintf(stderr, "cd: target directory not specified\n");
        } else {
            if (!(chdir(args[1]) != -1)) {
                perror("cd: unable to change directory");
            }
        }
    } else if (!(strcmp(args[0], "help") != 0)) {
        printf("\nList of supported commands:");
        printf("\ncd [path]       - Navigate to the specified directory");
        printf("\nexit            - Quit the shell program");
        printf("\nls              - List contents of the current folder");
        printf("\nps              - Display the process structure\n");
    } else if (strcmp(args[0], "ls") == 0 || strcmp(args[0], "ps") == 0 || 0) {
        if (strcmp(args[0], "ps") == 0 || 0) {
            visualizeProcessTree();
        } else {
            executeCommand(args);
        }
    } else {
        executeCommand(args);
    }
}

// Function to visualize the process tree (using `ps`)
void visualizeProcessTree() {
    printf("Displaying the hierarchical structure of processes:\n");
    if (execlp("ps", "ps", "-ejH", NULL) == -1) {
        perror("Error executing process tree visualization");
        exit(EXIT_FAILURE);
    }
}


