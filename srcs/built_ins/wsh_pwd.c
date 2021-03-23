#include "minishell.h"

void	wsh_pwd(t_wsh_list *wsh_list)
{
	// char	buff[4029];

	// getcwd(buff, 4029);
	// ft_putendl_fd(buff, 1);
	ft_putendl_fd(wsh_get_envar("PWD", wsh_list->wsh_envs), 1);
	if (wsh_list->ast_parsed->std_out != 1 || wsh_list->ast_parsed->wsh_redi)
		exit(0);
	return ;
}
