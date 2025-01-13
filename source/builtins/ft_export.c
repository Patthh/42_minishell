#include "../../include/minishell.h"

// handles without memory leaks
// export
// export a
// export a b c d e f g h
// export VAR=$USER
// export =
// export "="

// Test  24: ✅ export hello
// Test  25: ✅ export HELLO=123
// Test  26: ❌ export A-
// Test  27: ✅ export HELLO=123 A
// Test  28: ✅ export HELLO="123 A-"
// Test  29: ✅ export hello world
// Test  30: ❌ export HELLO-=123
// Test  31: ❌ export =
// Test  32: ❌ export 123
// Test  56: ✅ export GHOST=123 | env | grep GHOST

// prints formatted env
static void	export_print(const char *key, const char *value)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd((char *)key, STDOUT_FILENO);
	if (value && *value != '\0')
	{
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd((char *)value, STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static void	export_print_sorted(t_env **sorted, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		export_print(sorted[i]->key, sorted[i]->value);
		i++;
	}
}

void	ft_export(t_command *command, t_program *minishell)
{
	t_env	**sorted;
	int		size;
	int		i;

	if (!command->arguments[1])
	{
		sorted = export_sorting(minishell, &size);
		if (sorted)
		{
			export_print_sorted(sorted, size);
			free (sorted);
		}
		minishell->status = 0;
		return ;
	}
	i = 1;
	while (command->arguments[i])
		export_process(command->arguments[i++], minishell);
}
