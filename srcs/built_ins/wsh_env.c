#include "minishell.h"

void	wsh_env(char *env[])
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], 0);
		ft_putchar_fd('\n', 0);
		i++;
	}
	return ;
}