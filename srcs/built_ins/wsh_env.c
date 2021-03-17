#include "minishell.h"

void	wsh_env(t_wsh_list *wsh_list)
{
	int i;

	i = 0;
	while (wsh_list->wsh_envs[i] != 0)
	{
		if (wsh_findeq(wsh_list->wsh_envs[i]))
			ft_putendl_fd(wsh_list->wsh_envs[i], 1);
		i++;
	}
	if (wsh_list->ast_parsed->std_out == 1)
		return ;
	else
		exit(0);
}