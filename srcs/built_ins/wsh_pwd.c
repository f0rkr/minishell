#include "minishell.h"

void	wsh_pwd(t_wsh_list *wsh_list)
{
	char	*tmp;

	tmp = wsh_get_envar("PWD", wsh_list->wsh_envs);
	ft_putendl_fd(tmp, 1);
	wsh_free(&tmp);
	g_tab[0] = 0;
	if (wsh_list->ast_parsed->std_out != 1 || wsh_list->ast_parsed->wsh_redi)
		exit(0);
	return ;
}
