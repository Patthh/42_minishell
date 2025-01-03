### Preparation
- [x] Prepare data structures for parsing (`t_pipeline`, `t_command`)
- [x] Create a pipeline structure to hold commands (`t_pipeline`)
- [x] Prepare to track current command being built (`t_command`)

### Basic Token Processing
- [x] Iterate through tokens sequentially (`t_token`)
- [x] Handle different token types in order of complexity:
  - [x] Words/Command Names (`t_token`, `t_command`)
    - [x] First word becomes command name (`t_command->arguments[0]`)
    - [x] Subsequent words become arguments (`t_command->arguments`)
  - [x] Redirections (`t_redirection`)
    - [x] Capture redirection type (input, output, append, heredoc) (`t_redirection->type`)
    - [x] Associate filename with current command (`t_redirection->file`)
  - [x] Pipes (`t_pipeline`)
    - [x] Separate commands (`t_command`)
    - [x] Add previous command to pipeline (`t_pipeline->commands`)
    - [x] Prepare for next command (`t_command`)

### Argument Handling
- [x] Support multiple arguments per command (`t_command->arguments`)
- [ ] Limit argument count (prevent overflow) (`t_command->arg_count`)
- [ ] Handle quoted arguments (already processed by tokenizer) (`t_token->value`)

### Redirection Handling
- [x] Support input redirections (<) (`t_redirection->type`, `t_command->input`)
- [x] Support output redirections (>) (`t_redirection->type`, `t_command->output`)
- [x] Support append redirections (>>) (`t_redirection->type`, `t_command->output`)
- [x] Support heredoc redirections (<<) (`t_redirection->type`, `t_command->input`)
- [x] Ensure redirections attach to correct command (`t_command`)

### Error Checking
- [x] Validate token sequence (`t_token`)
- [x] Handle unexpected token combinations (`t_token`)
- [x] Manage memory allocation failures (`malloc`)
- [x] Detect and handle syntax errors (`t_token`, `t_pipeline`)

### Pipeline Finalization
- [x] Add last command to pipeline (`t_pipeline->commands`)
- [x] Ensure pipeline is ready for execution (`t_pipeline`)
- [x] Clean up any temporary structures (`t_command`, `t_redirection`)

### Post-Parsing
- [x] Prepare pipeline for execution stage (`t_pipeline`)
- [x] Free unused resources (`t_pipeline`, `t_command`, `t_redirection`)
- [x] Handle edge cases (empty input, single command, multiple commands) (`t_pipeline`)

### Advanced Considerations (Optional/Bonus)
- [x] Support command substitution (`t_token`, `t_pipeline`)
- [x] Handle environment variable expansion (`t_env`)
- [x] Prepare for bonus features (&&, ||, parentheses) (`t_pipeline`, `t_command`, `t_token`)

### Key Principles
- Keep parsing linear and straightforward
- Follow the subject's requirements exactly
- Minimal complexity
- Clear separation of concerns
- Robust error handling
