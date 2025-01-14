#include "../../include/minishell.h"

// static int	heredoc_content(t_redirection *heredoc)
// {
// 	heredoc->content = ft_strdup("");
// 	if (!heredoc->content)
// 	{
// 		ft_error("Heredoc: memoery allocation failed\n");
// 		return (0);
// 	}
// 	return (1);
// }

// static int	heredoc_append(t_redirection *heredoc, char *line)
// {
// 	char	*temp;
// 	char	*append;

// 	if (!heredoc->content || heredoc->content[0] == '\0')
// 		temp = ft_strdup(line);
// 	else
// 	{
// 		temp = ft_strjoin(heredoc->content, "\n");
// 		if (!temp)
// 		{
// 			ft_error("Heredoc: memory allocation failed\n");
// 			return (0);
// 		}
// 		append = ft_strjoin(temp, line);
// 		free (temp);
// 		temp = append;
// 	}
// 	if (!temp)
// 	{
// 		ft_error("Heredoc: memory allocation failed\n");
// 		return (0);
// 	}
// 	free (heredoc->content);
// 	heredoc->content = temp;
// 	return (1);
// }

// static int	heredoc_lines(t_redirection *heredoc)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || ft_strcmp(line, heredoc->filename) == 0)
// 		{
// 			free (line);
// 			rl_clear_history();
// 			return (1);
// 		}
// 		if (!heredoc_append(heredoc, line))
// 		{
// 			free (line);
// 			rl_clear_history();
// 			return (0);
// 		}
// 		add_history(line);
// 		free (line);
// 	}
// }

// static void	heredoc_expand(t_redirection *heredoc, t_program *minishell)
// {
// 	char	*expand;

// 	if (!heredoc || heredoc->quoted || !heredoc->content)
// 		return ;
// 	expand = quote_expand(heredoc->content, minishell);
// 	if (expand)
// 	{
// 		free (heredoc->content);
// 		heredoc->content = expand;
// 	}
// 	else
// 		ft_error("Heredoc: failed to expand heredoc\n");
// }

// void	heredoc_read(t_redirection *heredoc, t_command *command, t_program *minishell)
// {
// 	if (!heredoc)
// 		return ;
// 	if (!heredoc_content(heredoc))
// 		return ;
// 	if (!heredoc_lines(heredoc))
// 	{
// 		free (heredoc->content);
// 		heredoc->content = NULL;
// 		return ;
// 	}
// 	heredoc_expand(heredoc, minishell);
// 	if (!parser_argument(command, heredoc->content))
// 		ft_error("Heredoc: failed to add argument\n");
// 	free(heredoc->content);
// 	heredoc->content = NULL;
// }
void    heredoc_read(t_redirection *heredoc, t_command *command, t_program *minishell)
{
    int     pipe_fds[2];
    pid_t   pid;
    int     status;
    char    *line;

    if (!heredoc)
        return;
    if (pipe(pipe_fds) == -1)
    {
        ft_error("Heredoc: pipe creation failed\n");
        return;
    }
    signal(SIGINT, SIG_IGN);  // Parent ignores SIGINT during heredoc

    pid = fork();
    if (pid == -1)
    {
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        return;
    }

    if (pid == 0)  // Child process
    {
        signal(SIGINT, SIG_DFL);  // Child should handle SIGINT normally
        signal(SIGQUIT, SIG_IGN);
        close(pipe_fds[0]);  // Close read end in child

        // Make sure we're reading from terminal
        int tty_fd = open("/dev/tty", O_RDONLY);
        if (tty_fd != -1)
        {
            dup2(tty_fd, STDIN_FILENO);
            close(tty_fd);
        }

        while (1)
        {
            line = readline("> ");
            if (!line)  // EOF (Ctrl+D)
            {
                close(pipe_fds[1]);
                exit(0);
            }
            
            if (ft_strcmp(line, heredoc->filename) == 0)  // Delimiter found
            {
                free(line);
                close(pipe_fds[1]);
                exit(0);
            }

            // Handle variable expansion if not quoted
            if (!heredoc->quoted)
            {
                char *expanded = quote_expand(line, minishell);
                if (expanded)
                {
                    free(line);
                    line = expanded;
                }
            }
			// fprintf(stdout,"Debug line : %s\n", line);
            write(pipe_fds[1], line, ft_strlen(line));
            write(pipe_fds[1], "\n", 1);
            // fprintf(stderr, "Before freeing: %p, line: '%s' Cmd:\n", (void *)line, line);
			free(line);
			// line = NULL;
			// fprintf(stderr, "After freeing: line is set to NULL\n");
        }
    }

    // Parent process
    close(pipe_fds[1]);  // Close write end in parent
    waitpid(pid, &status, 0);
    signal(SIGINT, SIG_DFL);  // Restore default signal handling

    if (WIFSIGNALED(status))  // If child was terminated by a signal
    {
        close(pipe_fds[0]);
        minishell->status = 1;
        return;
    }
	if (!command || !command->arguments)  // Handle case with no command
    {
        // fprintf(stderr, "Debug: No command found, storing heredoc content.\n");
        // char buffer[4096];
        // ssize_t bytes;
        // while ((bytes = read(pipe_fds[0], buffer, sizeof(buffer) - 1)) > 0)
        // {
        //     buffer[bytes] = '\0';
        //     fprintf(stdout, "%s", buffer);  // Print heredoc content to stdout
        // }
        close(pipe_fds[0]);
        return;
    }
    // Set up the command's input
    if (command->fd_in != -1)
        close(command->fd_in);
    command->fd_in = pipe_fds[0];  // Set heredoc pipe as command input
}
// to test it
// cc -Wall -Werror -Wextra *.c  ../utils/utils_libft.c ../lexer/*.c ../utils/utils.c -lreadline -O0 -g

// int main(void)
// {
// 	t_redirection 	*heredoc = create_redirection("HEREDOC", "EOF", 0);
// 	t_program		*minishell = NULL;

// 	heredoc_read(heredoc, minishell);

// 	printf("%s\n", heredoc->content);
// 	free(heredoc->content);
// 	free(heredoc->type);
// 	free(heredoc->filename);
// 	free(heredoc);
// 	return (0);
// }
