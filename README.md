Simple_shell - A basic command-line interpreter

simple_shell is a simple command-line interpreter that provides a basic interface to the operating system. It supports command execution, file management, and various shell built-in commands.
#OPTIONS
bash
Copier le code
-i, --interactive
    Start the shell in interactive mode.
    
-c, --command <command>
    Execute the specified command and exit.
    
-h, --help
    Display this help and exit.
#COMMANDS
css
Copier le code
cd [directory]
    Change the current directory to the specified directory.

exit [status]
    Exit the shell with the given status code. If no status is provided, exit with the status of the last executed command.

env
    Display the current environment variables.

setenv [variable] [value]
    Set or modify an environment variable.

unsetenv [variable]
    Remove an environment variable.
    
history
    Display the history of executed commands.

alias [name]=[value]
    Create an alias for a command.

unalias [name]
    Remove an alias.
#FILES
bash
Copier le code
~/.simple_shell_history
    The history file that stores the command history.

~/.simple_shellrc
    Configuration file for initializing the shell environment.
#EXAMPLES
bash
Copier le code
Start the shell in interactive mode:
    $ simple_shell -i

Run a command:
    $ simple_shell -c "ls -l"

Set an environment variable:
    $ setenv PATH /usr/local/bin

Change directory:
    $ cd /home/user

source: Internet
