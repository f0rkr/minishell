#include "minishell.h"

int		searcheq(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	wsh_export(t_wsh_tokens *wsh_token,
t_wsh_list *wsh_list)
{
	(void)wsh_token;
	(void)wsh_list;
	// char	*temp;
	// int		i;
	// int 	j;
	// int		cond;

	// i = 0;
	// j = 0;
	// cond = 0;
	// if (!(temp = (char *)ft_malloc(sizeof(char) * 4029)))
	// 	return ;
	// while (wsh_list->wsh_envs[i++]);
	// i-=2;
	// ft_strlcpy(temp, wsh_list->wsh_envs[i], ft_strlen(wsh_list->wsh_envs[i])+1);
	// while (wsh_token->wsh_param[j])
	// {
	// 	cond = 0;
	// 	if (!(searcheq(wsh_token->wsh_param[j])))
	// 		cond = 1;
	// 	if (cond == 0)
	// 	{
	// 		wsh_free((void **) &wsh_list->wsh_envs[i]);
	// 		wsh_list->wsh_envs[i++] = ft_strdup(wsh_token->wsh_param[j]);
	// 	}
	// 	j++;
	// }
	// wsh_free((void **) &wsh_list->wsh_envs[i]);
	// wsh_list->wsh_envs[i++] = ft_strdup(temp);
	// wsh_free((void **) &temp);
	return ;
}