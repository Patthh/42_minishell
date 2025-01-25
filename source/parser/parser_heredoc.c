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
		line = readline(HEREDOC);
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
		ft_error("Heredoc: failed to expand heredoc");
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

