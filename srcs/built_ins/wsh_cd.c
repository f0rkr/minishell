#include "minishell.h"

void	wsh_cd(t_wsh_list *wsh_list)
{
	char *tmp;

	tmp = NULL;
	if (wsh_list->ast_parsed->wsh_param)
	{
		tmp = wsh_list->ast_parsed->wsh_param[0];
		if (ft_strncmp(wsh_list->ast_parsed->wsh_param[0], ".", 2) != 0)
			if (!(ft_isin('/', wsh_list->ast_parsed->wsh_param[0] + (ft_strlen(wsh_list->ast_parsed->wsh_param[0]) - 1))))
				wsh_list->ast_parsed->wsh_param[0] = ft_strjoin(wsh_list->ast_parsed->wsh_param[0], "/");
		if (chdir(wsh_list->ast_parsed->wsh_param[0]) != 0)
		{	
			opendir(wsh_list->ast_parsed->wsh_param[0]);
			if(errno != 0)
			{
				ft_putstr_fd("wsh: cd: ", 2);
				ft_putstr_fd(tmp, 2);
				ft_putstr_fd(": ", 2);
				ft_putendl_fd(strerror(errno), 2);
			}
		}
	}
	else if (wsh_get_envar("HOME", wsh_list->wsh_envs))
		chdir(ft_strjoin(wsh_get_envar("HOME", wsh_list->wsh_envs), "/"));
	free(tmp);
	return ;
}