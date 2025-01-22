#include "../../include/minishell.h"

static int	heredoc_content(t_redirection *heredoc)
{
	heredoc->content = ft_strdup("");
	if (!heredoc->content)
	{
		ft_error("Heredoc: memory allocation failed");
		return (0);
	}
	return (1);
}

static int	heredoc_append(t_redirection *heredoc, char *line)
{
	char	*temp;
	char	*append;

	if (!heredoc->content)
		return (0);
	if (heredoc->content[0] == '\0')
		temp = ft_strdup(line);
	else
	{
		temp = ft_strjoin(heredoc->content, "\n");
		if (!temp)
		{
			ft_error("Heredoc: memory allocation failed");
			return (0);
		}
		append = ft_strjoin(temp, line);
		free(temp);
		temp = append;
	}
	if (!temp)
		return (ft_error("Heredoc: memory allocation failed"), 0);
	free(heredoc->content);
	heredoc->content = temp;
	return (1);
}

static int	heredoc_lines(t_redirection *heredoc)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putendl_fd("warning: here-document at end-of-file", 2);
			rl_clear_history();
			return (1);
		}
		if (ft_strcmp(line, heredoc->filename) == 0)
		{
			rl_clear_history();
			return (free(line), 1);
		}
		if (!heredoc_append(heredoc, line))
		{
			rl_clear_history();
			return (free(line), 0);
		}
		add_history(line);
		free(line);
	}
}

static void	heredoc_expand(t_redirection *heredoc, t_program *minishell)
{
	char	*expand;

	if (!heredoc || heredoc->quoted || !heredoc->content)
		return ;
	expand = quote_expand(heredoc->content, minishell);
	if (expand)
	{
		free(heredoc->content);
		heredoc->content = expand;
	}
	else
	{
		ft_error("Heredoc: failed to expand heredoc");
	}
}

int	setup_heredoc(t_command *command, t_program *minishell)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	int		saved_stdin;
	size_t	len;
	ssize_t	written;

	if (!command || !command->heredoc)
		return (1);
	if (pipe(fd) == -1)
	{
		ft_error("minishell: pipe failed");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		ft_error("minishell: fork failed");
		return (1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		len = ft_strlen(command->heredoc->content);
		written = write(fd[1], command->heredoc->content, len);
		write(fd[1], "\n", 1);
		close(fd[1]);
		if (written == -1)
			exit(1);
		exit(0);
	}
	else
	{
		close(fd[1]);
		saved_stdin = dup(STDIN_FILENO);
		if (saved_stdin == -1)
		{
			close(fd[0]);
			return (1);
		}
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			close(fd[0]);
			close(saved_stdin);
			return (1);
		}
		waitpid(pid, &status, 0);
		close(fd[0]);
		if (WIFEXITED(status))
			minishell->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			minishell->status = 128 + WTERMSIG(status);
		return (0);
	}
}

void	heredoc_read(t_redirection *heredoc, t_command *command,
		t_program *minishell)
{
	if (!heredoc || !command || !command->heredoc)
		return ;
	if (!heredoc_content(heredoc))
		return ;
	if (!heredoc_lines(heredoc))
	{
		free(heredoc->content);
		heredoc->content = NULL;
		return ;
	}
	heredoc_expand(heredoc, minishell);
	if (command->heredoc)
	{
		if (command->heredoc != heredoc)
		{
			free(command->heredoc->content);
			command->heredoc->content = ft_strdup(heredoc->content);
			if (!command->heredoc->content)
			{
				ft_error("heredoc: memory allocation failed");
				return ;
			}
		}
	}
}
