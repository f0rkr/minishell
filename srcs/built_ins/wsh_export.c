#include "minishell.h"

void	wsh_export(t_wsh_tokens *wsh_token,
t_wsh_list *wsh_list)
{
	char	temp[4029];
	int		i;
	int 	j;

	i = 0;
	j = 0;
	while (wsh_list->wsh_envs[i++]);
	i--;
	ft_strlcpy(temp, (const char *)wsh_list->wsh_envs[i], ft_strlen(wsh_list->wsh_envs[i]));
	while (wsh_token->wsh_arg[j])
	{
		ft_strlcpy(wsh_list->wsh_envs[i++],
		wsh_token->wsh_arg[j], ft_strlen(wsh_token->wsh_arg[j]));
		j++;
	}
	ft_strlcpy(wsh_list->wsh_envs[i], (const char *)temp, ft_strlen(temp));
	return ;
}