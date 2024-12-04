# Minishell Lexer Implementation Guide

## Overview
The lexer (lexical analyzer) is responsible for breaking down the input string into meaningful tokens that can be processed by the parser.

## Objectives
- Tokenize input string
- Handle special characters
- Manage quotes
- Expand environment variables
- Prepare tokens for parsing

## Useful Libft Functions
### String Manipulation
- `ft_strlen()`: Determine string length
- `ft_strdup()`: Create string copies
- `ft_substr()`: Extract substrings
- `ft_strjoin()`: Concatenate strings
- `ft_split()`: Tokenize strings
- `ft_strchr()`: Find characters
- `ft_strncmp()`: Compare strings

### Memory Management
- `ft_calloc()`: Allocate and zero memory
- `ft_memset()`: Initialize memory
- `ft_memcpy()`: Copy memory

### Character Checks
- `ft_isalnum()`: Alphanumeric check
- `ft_isdigit()`: Digit check
- `ft_isalpha()`: Alphabetic check

## Token Types
```c
typedef enum e_token_type {
    TOKEN_WORD,           // Regular word/argument
    TOKEN_REDIRECT_IN,    // <
    TOKEN_REDIRECT_OUT,   // >
    TOKEN_REDIRECT_APPEND,// >>
    TOKEN_REDIRECT_HEREDOC,// <<
    TOKEN_PIPE,           // |
    TOKEN_ENV_VAR,        // $VARIABLE
    TOKEN_EXIT_STATUS,    // $?
    TOKEN_SPACE,          // Whitespace
    TOKEN_EOF             // End of input
} t_token_type;

typedef struct s_token {
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;
```

## Lexer Stages

### 1. Input Preprocessing
- Remove leading/trailing whitespaces
- Handle empty input
- Initialize token list

### 2. Quote Handling
- Track quote states (single, double, no quotes)
- Prevent splitting within quotes
- Handle escaped characters

### 3. Token Extraction
- Identify token types
- Handle special characters
- Manage environment variable expansion

### 4. Error Handling
- Detect unclosed quotes
- Validate token sequences
- Manage syntax errors

## Pseudocode
```c
t_token *lexer(char *input) {
    t_token *tokens = NULL;
    char *current = input;

    while (*current) {
        if (is_whitespace(*current)) {
            // Skip whitespaces
            continue;
        }

        if (is_special_char(*current)) {
            // Handle redirects, pipes
            add_special_token(&tokens, current);
        }

        if (is_quote(*current)) {
            // Handle quoted sections
            add_quoted_token(&tokens, &current);
        }

        if (is_env_var(*current)) {
            // Expand environment variables
            add_env_token(&tokens, &current);
        }

        // Add regular word token
        add_word_token(&tokens, &current);
    }

    return tokens;
}
```

## Detailed Implementation Steps
1. Create token structure
2. Implement quote handling
3. Develop token extraction logic
4. Add environment variable expansion
5. Implement error checking
6. Create token list management functions

## Recommended Testing Approach
- Simple commands
- Commands with quotes
- Environment variable expansions
- Mixed input types
- Edge cases (empty input, multiple spaces)

## Potential Challenges
- Handling nested quotes
- Complex environment variable expansions
- Managing memory for tokens
- Detecting syntax errors

## Performance Considerations
- Minimize memory allocations
- Use efficient string processing
- Implement robust error handling
