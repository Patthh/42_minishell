### Preparation
- [ ] Prepare data structures for parsing (`t_pipeline`, `t_command`)
- [ ] Create a pipeline structure to hold commands (`t_pipeline`)
- [ ] Prepare to track current command being built (`t_command`)

### Basic Token Processing
- [ ] Iterate through tokens sequentially (`t_token`)
- [ ] Handle different token types in order of complexity:
  - [ ] Words/Command Names (`t_token`, `t_command`)
    - [ ] First word becomes command name (`t_command->arguments[0]`)
    - [ ] Subsequent words become arguments (`t_command->arguments`)
  - [ ] Redirections (`t_redirection`)
    - [ ] Capture redirection type (input, output, append, heredoc) (`t_redirection->type`)
    - [ ] Associate filename with current command (`t_redirection->file`)
  - [ ] Pipes (`t_pipeline`)
    - [ ] Separate commands (`t_command`)
    - [ ] Add previous command to pipeline (`t_pipeline->commands`)
    - [ ] Prepare for next command (`t_command`)

### Argument Handling
- [ ] Support multiple arguments per command (`t_command->arguments`)
- [ ] Limit argument count (prevent overflow) (`t_command->arg_count`)
- [ ] Handle quoted arguments (already processed by tokenizer) (`t_token->value`)

### Redirection Handling
- [ ] Support input redirections (<) (`t_redirection->type`, `t_command->input`)
- [ ] Support output redirections (>) (`t_redirection->type`, `t_command->output`)
- [ ] Support append redirections (>>) (`t_redirection->type`, `t_command->output`)
- [ ] Support heredoc redirections (<<) (`t_redirection->type`, `t_command->input`)
- [ ] Ensure redirections attach to correct command (`t_command`)

### Error Checking
- [ ] Validate token sequence (`t_token`)
- [ ] Handle unexpected token combinations (`t_token`)
- [ ] Manage memory allocation failures (`malloc`)
- [ ] Detect and handle syntax errors (`t_token`, `t_pipeline`)

### Pipeline Finalization
- [ ] Add last command to pipeline (`t_pipeline->commands`)
- [ ] Ensure pipeline is ready for execution (`t_pipeline`)
- [ ] Clean up any temporary structures (`t_command`, `t_redirection`)

### Post-Parsing
- [ ] Prepare pipeline for execution stage (`t_pipeline`)
- [ ] Free unused resources (`t_pipeline`, `t_command`, `t_redirection`)
- [ ] Handle edge cases (empty input, single command, multiple commands) (`t_pipeline`)

### Advanced Considerations (Optional/Bonus)
- [ ] Support command substitution (`t_token`, `t_pipeline`)
- [ ] Handle environment variable expansion (`t_env`)
- [ ] Prepare for bonus features (&&, ||, parentheses) (`t_pipeline`, `t_command`, `t_token`)

### Key Principles
- Keep parsing linear and straightforward
- Follow the subject's requirements exactly
- Minimal complexity
- Clear separation of concerns
- Robust error handling
