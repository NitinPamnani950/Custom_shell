# Custom Shell Implementation

************************************************************************************************************************************************
## Overview

This C project creates a unique command-line shell. In addition to supporting built-in commands and I/O redirection, the shell offers an interactive command execution interface.


*************************************************************************************************************************************************
## Features

### Functional Requirements
1. **Command Execution**:

   - Accepts user input for commands.
   - Parses the input into arguments.
   - Executes commands using `fork`, `execvp`, and `waitpid` system calls.

2. **Built-in Commands**:

   - `cd [directory]`: Changes the current working directory.
   - `help`: Displays a list of supported commands.
   - `exit`: Exits the shell.

3. **I/O Redirection**:

   - Supports input redirection (`<`) and output redirection (`>`).

4. **Process Tree Visualization**:

   - The shell creates child processes using `fork()`.
   - Process tree can be visualized using:
     ```bash
     pstree > process_tree.png 

![snapshot of process tree](process_tree.png)

***************************************************************************************************************************************************

## Installation and Usage

### Prerequisites

- GCC compiler (for Linux/Mac).
- Basic knowledge of shell commands.

### Steps to Compile and Run

1. Extract the provided zip file.
2. Go to the extracted directory:
   ```bash
   cd Custom_shell
   ```
3. Compile the program using the provided Makefile:
   ```bash
   make
   ```
4. Run the shell:
   ```bash
   ./shell
   ```
5. To clean up compiled files:
   ```bash
   make clean
   ```

### Example Usage

- Run a custom program:
  ```bash
  ./fact 10
  ```

- Use built-in commands:
  ```bash
  cd /path/to/directory
  cd ..
  help
  exit
  pwd
  ls
  sleep
  ```

- Use I/O redirection:
  ```bash
  echo -e "Hello, this is a test.\nThis is the second line." > input.txt
  cat < input.txt
  echo "This is a new line of text" > output.txt
  cat output.txt
  echo "This is another line" >> output.txt
  ls > output.txt
  

*************************************************************************************************************************************************

## Files Included

1. `fact.c`: source code for factorial.
2. `shell.c`: Source code for the custom shell.
3. `Makefile`:  used For compiling the shell.
4. `README.md`: Documentation 
5. `process_tree.PNG`: Snapshot of the process tree 

*************************************************************************************************************************************************


