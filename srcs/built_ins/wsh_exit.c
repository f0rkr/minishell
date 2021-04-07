#include "minishell.h"

void	wsh_exit_helper(t_wsh_list *wsh_list)
{
	if (wsh_list->ast_parsed->wsh_param || wsh_list->ast_parsed->wsh_arg)
	{
		if (wsh_list->ast_parsed->wsh_param)
		{
			if (ft_strncmp(wsh_list->ast_parsed->wsh_param[0],
					"9223372036854775807", 20) == 0)
				exit(255);
		}
		else
			if (ft_strncmp(wsh_list->ast_parsed->wsh_arg[0],
					"-9223372036854775808", 21) == 0)
				exit(0);
	}	
}

void	wsh_errors(t_wsh_list *wsh_list, int *i, int j)
{
	if (*i == -1 || *i == 0)
	{
		if (*i == 0)
			*i = 255;
		ft_putstr_fd("bash: exit: ", 1);
		if (j == 1)
			ft_putstr_fd(wsh_list->ast_parsed->wsh_param[0], 1);
		else
			ft_putstr_fd(wsh_list->ast_parsed->wsh_arg[0], 1);
		ft_putendl_fd(": numeric argument required", 1);
	}
}

void	wsh_exit(t_wsh_list *wsh_list)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (wsh_list->ast_parsed->std_in == 0)
		ft_putendl_fd("exit", 1);
	wsh_exit_helper(wsh_list);
	if (wsh_tab_length(wsh_list->ast_parsed->wsh_param) > 2
		|| wsh_tab_length(wsh_list->ast_parsed->wsh_arg) > 2)
		return (ft_putstr_fd("wsh: exit: too many arguments\n", 1));
	if (wsh_list->ast_parsed->wsh_param || wsh_list->ast_parsed->wsh_arg)
	{
		if (wsh_list->ast_parsed->wsh_param)
		{
			j = 1;
			i = atoi(wsh_list->ast_parsed->wsh_param[0]);
		}
		else
			i = atoi(wsh_list->ast_parsed->wsh_arg[0]);
		wsh_errors(wsh_list, &i, j);
	}
	if (wsh_list->ast_parsed->std_in == 0)
		exit(i);
}
