#include "../../include/minishell.h"

int	sequence_next(t_token *current, t_program *minishell)
{
	if (!current->next || !current->next->value)
	{
		error_syntax("newline", minishell);
		return (0);
	}
	return (1);
}

int	sequence_operators(t_token *current, t_token *previous,
	t_program *minishell)
{
	if (previous && (ft_isredirect_token(previous)
			|| previous->type == TKN_PIPE))
	{
		if (ft_isredirect_token(current) || current->type == TKN_PIPE)
		{
			error_syntax(current->value, minishell);
			return (0);
		}
		if (!current->value || !*current->value)
		{
			error_syntax("newline", minishell);
			return (0);
		}
	}
	if (!previous && current->type == TKN_PIPE)
	{
		error_syntax("|", minishell);
		return (0);
	}
	return (1);
}

int	sequence_redirect(t_token *current, t_program *minishell)
{
	if (ft_isredirect_token(current))
	{
		if (!sequence_next(current, minishell))
			return (0);
		if (current->next->type == TKN_PIPE)
		{
			error_syntax("|", minishell);
			return (0);
		}
		if (ft_isredirect_token(current->next))
		{
			error_syntax(current->next->value, minishell);
			return (0);
		}
	}
	return (1);
}

int	sequence_pipes(t_token *current, t_program *minishell)
{
	if (current->type == TKN_PIPE)
	{
		if (!sequence_next(current, minishell))
			return (0);
		if (current->next->type == TKN_PIPE)
		{
			error_syntax("|", minishell);
			return (0);
		}
		if (ft_isredirect_token(current->next))
		{
			error_syntax(current->next->value, minishell);
			return (0);
		}
	}
	return (1);
}

int	sequence_heredoc(t_token *token, t_program *minishell)
{
	if (token->type == TKN_RDH)
	{
		if (!token->next)
		{
			error_syntax("newline", minishell);
			return (0);
		}
		return (1);
	}
	return (1);
}
