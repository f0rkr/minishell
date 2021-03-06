#include "minishell.h"

void	wsh_env(char *env[])
{
	int i;

	i = 0;
	while (env[i] != 0)
	{
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return ;
}