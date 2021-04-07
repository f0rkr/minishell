#include "minishell.h"

void	ft_printarg(t_wsh_tokens *wsh_token)
{
	int		i;

	i = 0;
	while (wsh_token->wsh_arg[i]
		&& !(ft_strncmp(wsh_token->wsh_arg[i], "-n", 3)))
		i++;
	while (wsh_token->wsh_arg[i])
	{
		ft_putstr_fd(wsh_token->wsh_arg[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
}

void	wsh_echo(t_wsh_tokens *wsh_token)
{
	int		i;
	int		newline;

	newline = 0;
	i = 0;
	if (wsh_token->wsh_arg)
	{
		if (!(ft_strncmp(wsh_token->wsh_arg[0], "-n", 3)))
			newline = 1;
		ft_printarg(wsh_token);
	}
	while (wsh_token->wsh_param && wsh_token->wsh_param[i])
	{
		ft_putstr_fd(wsh_token->wsh_param[i], 1);
		if (wsh_token->wsh_param[i + 1] && wsh_token->wsh_param[i][0] != EOL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!newline)
		ft_putchar_fd('\n', 1);
	g_tab[0] = 0;
	if (wsh_token->std_out != 1 || wsh_token->wsh_redi)
		exit(0);
	return ;
}
