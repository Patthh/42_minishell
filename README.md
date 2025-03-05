# 42 Minishell

<div id="desktop-banner">
<pre>
███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░
████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░
██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░
██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░
██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗
╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝
</pre>
</div>

## 📖 What is `minishell` 🐚?

<details>
<summary><b>A simplified version of a Unix shell (Bash)</b></summary><br>
<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Minishell is a project associated with the curriculum of École 42, a coding school known for its project-based learning approach.
The Minishell project uses the C programming language to create a simplified version of the Unix shell (Bash).
The goal of this project is to teach students about imperative programming, Unix system calls, and rigorous coding techniques while also assisting them in understanding how shells function.
</p>
</details>

## ✅ Status

<details>
<summary><b>Project completion status</b></summary><br>
<p align="center">
Completed on : 2025-01-27 <br><br>
<img src="https://i.ibb.co/MkpXyMXp/image.png" alt="Project Status">
</p>
</details>

## 🚀 Usage

To clone and compile:
```shell
git clone https://github.com/Patthh/42_minishell.git
cd 42_minishell && make
```

To run the shell:
```shell
./minishell
```

## ✨ Features

- 💻 Interactive prompt when waiting for commands
- 📜 Working command history (navigable with 🔼 and 🔽 keys)
- 🌐 No global variables used
- 📁 Support for local executables with proper `$SHLVL` handling
- 💲 Environment variable expansion (`$VAR` and `$?` for last exit status)
- 📤 Input/output redirections:
  - `>` redirect output
  - `>>` redirect output in append mode
  - `<` redirect input
  - `<<` HEREDOC functionality with delimiters
- ⌨️ Signal handling:
  - `ctrl-C` displays a new line
  - `ctrl-D` exits minishell
  - `ctrl-L` clears the screen
  - `ctrl-\` does nothing in interactive mode
- 🚨 Signal-specific error messages on foreground process termination
- 🔍 Wildcard support for file matching

> [!WARNING]
> Shell operators `\`, `;`, `&&` and `||` are not implemented

## 🛠️ Built-in Commands

<details>
<summary><b>Implemented Built-in Commands</b></summary><br>
<p>Here are the built-in commands implemented in this Minishell:</p>

| Command | Description |
|---------|-------------|
| 🗣️ `echo` | Displays text; handles `-n` option |
| 📂 `cd` | Changes directory; supports relative/absolute paths |
| 📍 `pwd` | Prints current working directory |
| ⚙️ `export` | Sets/displays environment variables |
| 🗑️ `unset` | Unsets environment variables |
| 📋 `env` | Displays environment variables |
| 🚪 `exit` | Exits shell; handles exit codes |

</details>

> [!NOTE]
> "This project might take away your joy and happiness"

<div align="center">
  <img src="https://media1.tenor.com/m/MYZgsN2TDJAAAAAC/this-is.gif" width="400" alt="This is Minishell">
  <br>
  <i>A journey into shell implementation</i><br><br><br>
</div>

---
<div align="center">
  <p>Made with ❤️ and lots of 🅟🅐🅘🅝</p>
</div>
