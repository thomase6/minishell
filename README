# MiniShell

*This project has been created as part of the 42 curriculum by texenber and stbagdah.*

---

## Description

MiniShell is a simplified Unix shell written in C.
The goal of this project is to recreate the core behavior of a shell by interpreting user input, executing commands, and managing processes and environment variables.

It is designed to follow the subject requirements of the 42 curriculum and mimic standard shell behavior where specified.

---

## Mandatory Features

### Core Behavior

* Display a prompt when waiting for input
* Maintain a working command history
* Execute commands using `PATH`, relative, or absolute paths
* Handle environment variables and exit status (`$?`)
* Use at most one global variable for signal handling

### Parsing & Input Handling

* Handle single quotes `'` (no interpretation inside)
* Handle double quotes `"` (allow `$` expansion only)
* Do not interpret unsupported characters (e.g. `\`, `;`)
* Expand environment variables (`$VAR`)

### Redirections

* `<` input redirection
* `>` output redirection
* `>>` output append
* `<<` heredoc (without adding to history)

### Pipes

* Implement pipelines (`|`) connecting multiple commands

### Signals (Interactive Mode)

* `Ctrl-C` → display new prompt
* `Ctrl-D` → exit shell
* `Ctrl-\` → ignored

### Built-in Commands

* `echo` (with `-n`)
* `cd` (relative or absolute path only)
* `pwd`
* `export`
* `unset`
* `env`
* `exit`

---

## Instructions

### Compilation

make
make re
make clean
make fclean
```

### Execution

./minishell

---

## Resources

### Documentation

* Unix manual pages (`readline`, `fork`, `execve`, `pipe`, `dup2`)
* Bash behavior reference

### AI Usage

AI tools were used to:

* Explain system calls and shell behavior
* Assist debugging and edge cases
* Improve documentation clarity
