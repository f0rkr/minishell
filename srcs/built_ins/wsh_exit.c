#include "minishell.h"

void	wsh_exit(t_wsh_list *wsh_list)
{
	ft_putendl_fd("exit", 1);
	if (wsh_tab_length(wsh_list->ast_parsed->wsh_param) > 2)
	{
		ft_putstr_fd("wsh: exit: too many arguments\n", 1);
		return ;
	}
	if (wsh_list->ast_parsed->wsh_param && wsh_list->ast_parsed->wsh_param[0][0] == -1)
	{
		ft_putstr_fd("bash: exit: ", 1);
		ft_putstr_fd(wsh_list->ast_parsed->wsh_param[0], 1);
		ft_putendl_fd(": numeric argument required", 1);
	}
	exit(0);
}