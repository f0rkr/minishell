#include "minishell.h"

char	**ft_tmparr(char **env, int i)
{
	char	**tmp;
	int		j;
	int k;

	j = 0;
	k = i;
	while (env[i++]);
	if (!(tmp = malloc(sizeof(char **) * (i - k))))
		return (NULL);
	i = k;
	printf("%d", i);
	while (env[i])
	{
		if (!(tmp[j] = malloc(sizeof(char *) * 1024)))
			return (NULL);
		ft_strlcpy(tmp[j], env[i], ft_strlen(env[i]));
		i++;
		j++;
	}
	printf("%s", tmp[0]);
	tmp[j] = 0;
	return (tmp);
}

void	wsh_unset(t_wsh_tokens *wsh_token, t_wsh_list *wsh_list)
{
	int	i;
	int j;
	char **arr;

	i = 0;
	while (wsh_list->wsh_envs[i] != NULL)
	{
		j = 0;
		while (wsh_token->wsh_param[j][0] != '\0')
		{
			if (wsh_list->wsh_envs[i][0] == wsh_token->wsh_param[j][0])
			{
				if (!(ft_strncmp(wsh_list->wsh_envs[i], wsh_token->wsh_param[j], ft_strlen(wsh_token->wsh_param[j]))))
				{
					arr = ft_tmparr(wsh_list->wsh_envs, i + 1);
					wsh_free((void *)wsh_list->wsh_envs[i]);
					wsh_list->wsh_envs[i] = NULL;
				}
			}
			j++;
		}
		i++;
	}
	return ;
}