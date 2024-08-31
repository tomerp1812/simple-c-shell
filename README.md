# simple-c-shell
A basic shell implementation written in C.

The program supports executing commands, handling built-in commands (`cd`, `history`, `exit`), and managing the `PATH` environment variable.
It also tracks the history of commands entered during the session.

## Features

- **Command Execution**: Executes external commands using `fork` and `execvp`.
- **Built-in Commands**:
  - `cd <directory>`: Changes the current working directory.
  - `history`: Displays a history of commands with their process IDs (PIDs).
  - `exit`: Exits the shell.
- **Environment Variable Management**: Sets the `PATH` environment variable to include additional directories specified as command-line arguments.
- **Command History**: Keeps a history of commands entered and displays them upon request.

## Usage

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/tomerp1812/simple-c-shell.git
   cd simple-c-shell
   ```
2. **Compile the Program:**
   ```bash
   gcc -o myshell myshell.c
   ```
3. **Run the Shell:**
   ```bash
   ./myshell [additional-paths...]
   ```
4. **Commands:**
   - `cd <directory>`: Change the current directory.
   - `history`: Show the history of commands.
   - `exit`: Exit the shell.
   - External Commands: Execute any available command in the current `PATH`.
