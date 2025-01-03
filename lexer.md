# Minishell Progress Report

## Overview
The Minishell project aims to create a simple shell that can execute basic commands and handle input/output redirection. The project is divided into several components, including the lexer, parser, and built-in commands.

---

## Lexer
- [x] Tokenize input strings into a linked list of tokens.
- [x] Handle different token types (e.g., words, operators, redirections).
- [x] Handle quote handling (single and double quotes).
- [x] Handle environment variables (`$` followed by a sequence of characters).
- [ ] Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.

---

## Parser
- [x] Parse tokens into a pipeline of commands.
- [x] Handle command sequences, redirections, and pipes.
- [x] Handle advanced redirection scenarios (e.g., `<`, `>`, `>>`, `<<`).
- [x] Implement pipes (`|` character).
- [x] Handle redirections:
  - [x] `<` should redirect input.
  - [x] `>` should redirect output.
  - [x] `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen.
  - [x] `>>` should redirect output in append mode.

---

## Built-in Commands
- [ ] `cd`: Change the current working directory.
- [x] `pwd`: Print the current working directory.
- [x] `exit`: Exit the shell.
- [x] `echo`: Print arguments to the standard output.
- [x] `env`: Print the environment variables.
- [x] `unset`: Remove environment variables.
- [ ] `export`: Set environment variables.

---

## Heredoc (`<<`) Handling
- [x] Tokenize heredoc delimiters correctly.
- [x] Handle unquoted delimiters.
- [x] Handle single-quoted delimiters (treat as literal strings).
- [x] Handle double-quoted delimiters (treat as literal strings).
- [x] Handle delimiters with special characters (e.g., `EOF@#`).
- [x] Handle empty delimiters (syntax error).
- [x] Handle multiple heredocs in a single command.
- [x] Handle heredocs with spaces in delimiters.
- [ ] Handle heredocs with newlines in delimiters.
- [ ] Handle variable expansion within heredoc input (for double-quoted delimiters).
- [ ] Handle indentation in heredoc input.

---

## Next Steps
1. **Implement Variable Expansion in Heredocs:**
   - Expand variables within heredoc input when the delimiter is double-quoted.
   - Example:
     ```bash
     VAR="Hello"
     cat << "EOF"
     $VAR
     EOF
     ```
     Should output:
     ```
     Hello
     ```

2. **Handle Indentation in Heredocs:**
   - Preserve indentation in heredoc input for better readability.
   - Example:
     ```bash
     cat << EOF
         Indented line
     EOF
     ```
     Should output:
     ```
         Indented line
     ```

3. **Implement `export` Command:**
   - Add support for setting environment variables using the `export` command.

4. **Test and Refine:**
   - Conduct thorough testing for edge cases, including:
     - Heredocs with nested commands.
     - Heredocs with complex delimiters.
     - Heredocs with large input.
