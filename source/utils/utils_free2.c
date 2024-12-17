#include "../../include/minishell.h"

static void	free_input(t_redirection *input)
{
	t_redirection	*temp;

	while (input)
	{
		temp = input;
		input = input->next;
		free(temp->type);
		free(temp->filename);
		free(temp);
	}
}

static void	free_output(t_redirection *output)
{
	t_redirection	*temp;

	while (output)
	{
		temp = output;
		output = output->next;
		free(temp->type);
		free(temp->filename);
		free(temp);
	}
}

static void	free_command(t_command *command)
{
	int	i;

	i = 0;
	if (command->arguments)
	{
		while (command->arguments[i])
		{
			free(command->arguments[i]);
			i++;
		}
		free(command->arguments);
	}
	free_input(command->input);
	free_output(command->output);
	free(command);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	if (!pipeline)
		return ;
	while (i < pipeline->cmd_count)
	{
		free_command(pipeline->commands[i]);
		pipeline->commands[i] = NULL;
		i++;
	}
	free(pipeline->commands);
	pipeline->commands = NULL;
	free(pipeline);
}

void	free_parser(t_pipeline *pipeline)
{
	if (pipeline)
	{
		free_pipeline(pipeline);
		free (pipeline);
	}
}
