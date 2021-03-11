#include "minishell.h"

void	wsh_env(t_wsh_list *wsh_list)
{
	int i;

	i = 0;
	while (wsh_list->wsh_envs[i] != 0)
		ft_putendl_fd(wsh_list->wsh_envs[i++], 1);
	exit(0);
}