#include "../../include/minishell.h"

static int	heredoc_content(t_redirection *heredoc)
{
	heredoc->content = ft_strdup("");
	if (!heredoc->content)
	{
		ft_error("Heredoc: memoery allocation failed\n");
		return (0);
	}
	return (1);
}

static int	heredoc_append(t_redirection *heredoc, char *line)
{
	char	*temp;
	char	*append;

	if (!heredoc->content || heredoc->content[0] == '\0')
		temp = ft_strdup(line);
	else
	{
		temp = ft_strjoin(heredoc->content, "\n");
		if (!temp)
		{
			ft_error("Heredoc: memory allocation failed\n");
			return (0);
		}
		append = ft_strjoin(temp, line);
		free (temp);
		temp = append;
	}
	if (!temp)
	{
		ft_error("Heredoc: memory allocation failed\n");
		return (0);
	}
	free (heredoc->content);
	heredoc->content = temp;
	return (1);
}

static int	heredoc_lines(t_redirection *heredoc)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, heredoc->filename) == 0)
		{
			free (line);
			rl_clear_history();
			return (1);
		}
		if (!heredoc_append(heredoc, line))
		{
			free (line);
			rl_clear_history();
			return (0);
		}
		add_history(line);
		free (line);
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
		free (heredoc->content);
		heredoc->content = expand;
	}
	else
		ft_error("Heredoc: failed to expand heredoc\n");
}

void	heredoc_read(t_redirection *heredoc, t_command *command,
	t_program *minishell)
{
	if (!heredoc)
		return ;
	if (!heredoc_content(heredoc))
		return ;
	if (!heredoc_lines(heredoc))
	{
		free (heredoc->content);
		heredoc->content = NULL;
		return ;
	}
	heredoc_expand(heredoc, minishell);
	if (!parser_argument(command, heredoc->content))
		ft_error("Heredoc: failed to add argument\n");
	free(heredoc->content);
	heredoc->content = NULL;
}
