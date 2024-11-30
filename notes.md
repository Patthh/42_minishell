minishell/
│
├── include/
│   ├── minishell.h          # Main header file
│   ├── lexer.h              # Lexer header
│   ├── parser.h             # Parser header
│   └── executor.h           # Executor header
│
├── src/
│   ├── main.c               # Entry point
│   ├── prompt.c             # Prompt handling
│   │
│   ├── lexer/
│   │   ├── tokenize.c       # Tokenization logic
│   │   └── token_utils.c    # Token manipulation utilities
│   │
│   ├── parser/
│   │   ├── parse_command.c  # Command parsing
│   │   └── parse_utils.c    # Parsing utilities
│   │
│   ├── executor/
│   │   ├── execute.c        # Command execution
│   │   └── builtin.c        # Builtin command implementations
│   │
│   └── utils/
│       ├── error.c          # Error handling
│       └── memory.c         # Memory management
│
├── Makefile
└── README.md
