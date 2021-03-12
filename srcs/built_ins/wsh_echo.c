#include "minishell.h"

void	ft_printarg(t_wsh_tokens *wsh_token)
{
	int i;

	i = 0;
	while (wsh_token->wsh_arg[i] && !(ft_strncmp(wsh_token->wsh_arg[i], "-n", 3)))
		i++;
	while (wsh_token->wsh_arg[i])
	{
		ft_putstr_fd(wsh_token->wsh_arg[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
}

void	wsh_echo(t_wsh_tokens *wsh_token, char **env)
{
	int i;
	int newline;
	int j;
	
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
		j = 0;
		while (wsh_token->wsh_param[i][j])
		{
			if (wsh_token->wsh_param[i][j] == '$')
			{
				if (wsh_get_envar(wsh_token->wsh_param[i] + (j + 1), env))
				{
					ft_putstr_fd(wsh_get_envar(wsh_token->wsh_param[i] + (j + 1), env), 1);
					while (wsh_token->wsh_param[i][j])
					{
						if (wsh_token->wsh_param[i][j] == ' ' || wsh_token->wsh_param[i][j] == '\0')
							break;
						j++;
					}
					j--;
				}
				else
					ft_putchar_fd('\n', 1);
			}
			else
				ft_putchar_fd(wsh_token->wsh_param[i][j], 1);
			j++;
		}
		if (wsh_token->wsh_param[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!newline)
		ft_putchar_fd('\n', 1);
	exit(0);
}