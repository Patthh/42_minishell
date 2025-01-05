## Minishell Progress Report

### **Lexer**

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
- [ ] Handle wildcard expansion (* and ? characters)
  - [ ] Edge case: No matching files
  - [ ] Edge case: Wildcard at the beginning/end of the input
  - [ ] Edge case: Invalid wildcard characters
  - [ ] Edge case: Wildcard in the middle of a word (e.g., `file*.txt`)
  - [ ] Edge case: Wildcard in quotes (should not expand)

### **Parser**

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
- [x] Handle redirections:
  - [x] < should redirect input.
        - [x] Edge case: File not found.
        - [x] Edge case: File not readable.
        - [x] Edge case: File is a directory.
  - [x] > should redirect output.
        - [x] Edge case: File cannot be created.
        - [x] Edge case: File not writable.
        - [x] Edge case: File is a directory.
  - [x] << should be given a delimiter, then read the input until a line containing the delimiter is seen.
        - [x] Edge case: No delimiter specified.
        - [x] Edge case: Delimiter not found - [x] Edge case: Delimiter on the same line as <<.
  - [x] >> should redirect output in append mode.
        - [x] Edge case: File cannot be opened for appending.
        - [x] Edge case: File is a directory.
- [ ] Handle logical operators (&& and ||).
    - [ ] Edge case: Mismatched parentheses.
    - [ ] Edge case: Complex expressions with multiple operators.
    - [ ] Edge case: Logical operators with no commands.
- [ ] Handle parentheses (( and )).
    - [ ] Edge case: Unbalanced parentheses.
    - [ ] Edge case: Nested parentheses.
    - [ ] Edge case: Parentheses with no commands inside.


**Execution**

- [ ] Execute commands in the pipeline.
    - [ ] Edge case: Command not found.
    - [ ] Edge case: Incorrect path.
    - [ ] Edge case: Invalid arguments to the command.
- [ ] Handle built-in commands:
  -   [ ] cd: Change the current working directory.
        - [ ] Edge case: Invalid path (e.g., non-existent directory).
        - [ ] Edge case: Empty path.
        - [ ] Edge case: Path containing special characters.
  -   [ ] pwd: Print the current working directory.
        - [ ] Edge case: Current directory is root.
        - [ ] Edge case: Path contains special characters.
  -   [ ] exit: Exit the shell.
        - [ ] Edge case: Exit during command execution.
  -   [ ] echo: Print arguments to the standard output.
        - [ ] Edge case: No arguments to echo.
        - [ ] Edge case: Multiple arguments with -n.
        - [ ] Edge case: Escaped characters within arguments.
  -   [ ] env: Print the environment variables.
        - [ ] Edge case: No environment variables set.
        - [ ] Edge case: Environment variables with special characters.
  -   [ ] unset: Remove environment variables.
        - [ ] Edge case: Unsetting an unset variable.
        - [ ] Edge case: Unsetting a built-in variable.
  -   [ ] export: Set environment variables.
        - [ ] Edge case: Exporting an existing variable.
        - [ ] Edge case: Exporting a variable with special characters.
- [ ] Handle external commands (e.g., /bin/ls, /usr/bin/cat).
    - [ ] Edge case: Command execution fails.
    - [ ] Edge case: Command signals an error.
- [ ] Handle redirections during execution.
    - [ ] Edge case: Redirection to/from a device (e.g., /dev/null).
- [ ] Handle pipes during execution.
    - [ ] Edge case: Pipe between two redirections.
- [ ] Handle logical operators during execution.
    - [ ] Edge case: Short-circuit evaluation (&& and ||).
- [ ] Handle parentheses during execution.
    - [ ] Edge case: Nested parentheses.

**Heredoc (<<) Handling**

- [ ] Tokenize heredoc delimiters correctly.
    - [ ] Edge case: Delimiter contains whitespace.
    - [ ] Edge case: Delimiter contains special characters.
- [ ] Handle unquoted delimiters.
    - [ ] Edge case: Unquoted delimiter contains special characters.
- [ ] Handle single-quoted delimiters (treat as literal strings).
    - [ ] Edge case: Nested single quotes within the delimiter.
- [ ] Handle double-quoted delimiters (treat as literal strings).
    - [ ] Edge case: Variable expansion within the delimiter.
- [ ] Handle delimiters with special characters (e.g., EOF@#).
    - [ ] Edge case: Delimiter contains invalid characters.
- [ ] Handle empty delimiters (syntax error).
- [ ] Handle multiple heredocs in a single command.
- [ ] Handle heredocs with spaces in delimiters.
- [ ] Handle heredocs with newlines in delimiters.
- [ ] Handle variable expansion within heredoc input (for double-quoted delimiters).
    - [ ] Edge case: Variable not found.
- [ ] Handle indentation in heredoc input.
    - [ ] Edge case: Indentation before the delimiter.

**Signals**

- [ ] Handle signals (e.g., SIGINT, SIGQUIT, SIGTERM).
    - [ ] Edge case: Signal received during command execution.
    - [ ] Edge case: Signal received during long-running commands.

**Error Handling**

- [ ] Handle errors during execution (e.g., file not found, permission denied).
    - [ ] Edge case: Display appropriate error messages.
- [ ] Handle errors during parsing (e.g., syntax errors).
    - [ ] Edge case: Display informative syntax error messages.
- [ ] Handle errors during tokenization (e.g., invalid characters).
    - [ ] Edge case: Display error messages for specific invalid characters.

---

**Mandatory Part**

## Prompt & History

- [ ] Display a prompt when waiting for a new command.
    - [ ] Edge case: Empty prompt.
    - [ ] Edge case: Custom prompt using environment variables (e.g., `PS1`).
- [ ] Have a working history.
    - [ ] Edge case: Empty history.
    - [ ] Edge case: History size limits (optional).
    - [ ] Edge case: Handling history navigation commands (e.g., up/down arrows).

## Command Execution

- [ ] Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
    - [ ] Edge case: Command not found.
    - [ ] Edge case: Incorrect path.
    - [ ] Edge case: Invalid characters in command name.
    - [ ] Edge case: Command with spaces in its name.

## Signal Handling

- [ ] Handle ctrl-C, ctrl-D, and ctrl-\ as expected.
    - [ ] Edge case: ctrl-C during command execution.
    - [ ] Edge case: ctrl-C during
