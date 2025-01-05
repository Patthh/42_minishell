# Minishell Progress Report

## Mandatory Part

### Lexer

- [x] Tokenize input strings into a linked list of tokens
  - [x] Edge case: Handle empty input string
  - [x] Edge case: Handle input string with only whitespace
  - [ ] Edge case: Handle invalid characters (e.g., control characters) (to execution SIGNAL)
  - [x] Edge case: Handle input with mixed whitespace (tabs, spaces, newlines)
  - [x] Edge case: Handle input with leading/trailing whitespace
- [x] Handle different token types (e.g., words, operators, redirections)
  - [x] Edge case: Handle multiple consecutive operators (e.g., `>>`, `<<`, `||`, `&&`)
  - [x] Edge case: Handle operators at the beginning/end of input
- [x] Handle quote handling (single and double quotes)
  - [x] Edge case: Unmatched quotes
  - [x] Edge case: Nested quotes
  - [x] Edge case: Quotes at the beginning/end of the input
  - [x] Edge case: Empty quotes (`''` or `""`)
  - [x] Edge case: Quotes containing only whitespace
- [x] Handle environment variables ($ followed by a sequence of characters)
  - [x] Edge case: Variable name not found
  - [x] Edge case: Variable name contains special characters ("_-.")
  - [x] Edge case: Empty variable name
  - [x] Edge case: Variable name starting with a number
  - [x] Edge case: Variable name with mixed case (e.g., `$PATH`, `$path`)
- [x] Handle $? which should expand to the exit status of the most recently executed foreground pipeline
  - [x] Edge case: No previous command executed
  - [x] Edge case: Previous command was a built-in
  - [x] Edge case: $? in the middle of a command

### Parser

- [x] Parse tokens into a pipeline of commands.
    - [x] Edge case: Empty command.
    - [x] Edge case: Multiple consecutive pipes.
    - [x] Edge case: Pipe at the beginning/end of the input.
    - [x] Edge case: Command with no arguments.
    - [x] Edge case: Command with only redirections.
- [x] Handle command sequences, redirections, and pipes.
    - [x] Edge case: Invalid command sequence order (e.g., redirection before command).
    - [x] Edge case: Redirection after a pipe.
    - [x] Edge case: Multiple redirections for the same command.
- [x] Handle advanced redirection scenarios (e.g., <, >, >>, <<).
    - [x] Edge case: Multiple redirections to the same file.
    - [x] Edge case: Redirection to/from a device (e.g., /dev/null).
    - [x] Edge case: Redirection to/from a directory.
    - [x] Edge case: Redirection with no filename specified.
- [x] Implement pipes (| character).
    - [x] Edge case: Pipe between two redirections.
    - [x] Edge case: Pipe with no command on one side.
    - [x] Edge case: Pipe with no command on either side.

### Execution

- [x] Execute commands in the pipeline.
    - [x] Edge case: Command not found.
    - [x] Edge case: Incorrect path.
    - [x] Edge case: Invalid arguments to the command.
- [x] Handle built-in commands:
  -   [ ] cd: Change the current working directory.
        - [ ] Edge case: Invalid path (e.g., non-existent directory).
        - [ ] Edge case: Empty path.
        - [ ] Edge case: Path containing special characters.
  -   [x] pwd: Print the current working directory.
        - [x] Edge case: Current directory is root.
        - [x] Edge case: Path contains special characters.
  -   [x] exit: Exit the shell.
        - [x] Edge case: Exit during command execution.
  -   [x] echo: Print arguments to the standard output.
        - [x] Edge case: No arguments to echo.
        - [x] Edge case: Multiple arguments with -n.
        - [x] Edge case: Escaped characters within arguments.
  -   [x] env: Print the environment variables.
        - [x] Edge case: No environment variables set.
        - [x] Edge case: Environment variables with special characters.
  -   [ ] unset: Remove environment variables.
        - [ ] Edge case: Unsetting an unset variable.
        - - [ ] Edge case: Invalid variable name.
  -   [ ] export: Set environment variables.
        - [ ] Edge case: Invalid variable name.
        - [ ] Edge case: Variable name already exists.

## Bonus Part

- [ ] Implement logical operators (&& and ||) with parenthesis for priorities.
- [ ] Implement wildcard (*) functionality for the current working directory.
