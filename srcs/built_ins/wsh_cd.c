#include "minishell.h"

void	wsh_cd(t_wsh_tokens *wsh_token)
{
	char *tmp;

	tmp = NULL;
	if (wsh_token->wsh_param)
	{
		tmp = wsh_token->wsh_param[0];
		if (ft_strncmp(wsh_token->wsh_param[0], ".", 2) != 0)
			if (!(ft_isin('/', wsh_token->wsh_param[0] + (ft_strlen(wsh_token->wsh_param[0]) - 1))))
				wsh_token->wsh_param[0] = ft_strjoin(wsh_token->wsh_param[0], "/");
		if (chdir(wsh_token->wsh_param[0]) != 0)
		{	
			opendir(wsh_token->wsh_param[0]);
			if(errno != 0)
			{
				ft_putstr_fd("wsh: cd: ", 2);
				ft_putstr_fd(tmp, 2);
				ft_putstr_fd(": ", 2);
				ft_putendl_fd(strerror(errno), 2);
			}
		}
	}
	// else ($HOME)
	// 	chdir("/Users/oel-ouar/");
	free(tmp);
	return ;
}