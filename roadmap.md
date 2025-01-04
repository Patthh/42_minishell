## Minishell Progress Report

**Lexer**

- [x] Tokenize input strings into a linked list of tokens.
- [x] Handle different token types (e.g., words, operators, redirections).
- [x] Handle quote handling (single and double quotes).
- [x] Handle environment variables ($ followed by a sequence of characters).
- [x] Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
- [ ] Handle wildcard expansion (* and ? characters).

**Parser**

- [x] Parse tokens into a pipeline of commands.
- [x] Handle command sequences, redirections, and pipes.
- [x] Handle advanced redirection scenarios (e.g., <, >, >>, <<).
- [x] Implement pipes (| character).
- [x] Handle redirections:
  -   [x] < should redirect input.
  -   [x] > should redirect output.
  -   [x] << should be given a delimiter, then read the input until a line containing the delimiter is seen.
  -   [x] >> should redirect output in append mode.
- [ ] Handle logical operators (&& and ||).
- [ ] Handle parentheses (( and )).

**Execution**

- [ ] Execute commands in the pipeline.
- [ ] Handle built-in commands:
  -   [ ] cd: Change the current working directory.
  -   [x] pwd: Print the current working directory.
  -   [x] exit: Exit the shell.
  -   [x] echo: Print arguments to the standard output.
  -   [x] env: Print the environment variables.
  -   [x] unset: Remove environment variables.
  -   [ ] export: Set environment variables.
- [ ] Handle external commands (e.g., /bin/ls, /usr/bin/cat).
- [ ] Handle redirections during execution.
- [ ] Handle pipes during execution.
- [ ] Handle logical operators during execution.
- [ ] Handle parentheses during execution.

**Heredoc (<<) Handling**

- [x] Tokenize heredoc delimiters correctly.
- [x] Handle unquoted delimiters.
- [x] Handle single-quoted delimiters (treat as literal strings).
- [x] Handle double-quoted delimiters (treat as literal strings).
- [x] Handle delimiters with special characters (e.g., EOF@#).
- [x] Handle empty delimiters (syntax error).
- [x] Handle multiple heredocs in a single command.
- [x] Handle heredocs with spaces in delimiters.
- [x] Handle heredocs with newlines in delimiters.
- [x] Handle variable expansion within heredoc input (for double-quoted delimiters).
- [x] Handle indentation in heredoc input.

**Signals**

- [ ] Handle signals (e.g., SIGINT, SIGQUIT, SIGTERM).

**Error Handling**

- [ ] Handle errors during execution (e.g., file not found, permission denied).
- [ ] Handle errors during parsing (e.g., syntax errors).
- [ ] Handle errors during tokenization (e.g., invalid characters).
