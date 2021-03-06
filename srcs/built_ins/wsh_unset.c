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
	while (env[i])
	{
		if (!(tmp[j] = malloc(sizeof(char *) * ft_strlen(env[i]))))
			return (NULL);
		ft_strlcpy(tmp[j], env[i], ft_strlen(env[i]) + 1);
		i++;
		j++;
	}
	tmp[j] = 0;
	return (tmp);
}

void	wsh_unset(t_wsh_tokens *wsh_token, t_wsh_list *wsh_list)
{
	int	i;
	int j;
	char **arr;
	int k;

	i = 0;
	while (wsh_list->wsh_envs[i] != NULL)
	{
		j = 0;
		while (wsh_token->wsh_param[j] != NULL)
		{
			if (wsh_list->wsh_envs[i][0] == wsh_token->wsh_param[j][0])
			{
				if (!(ft_strncmp(wsh_list->wsh_envs[i], before_eq(wsh_token->wsh_param[j]), ft_strlen(before_eq(wsh_token->wsh_param[j])))))
				{
					k = 0;
					arr = ft_tmparr(wsh_list->wsh_envs, i + 1);
					while (arr[k])
					{
						wsh_list->wsh_envs[i + k] = arr[k];
						k++;
					}
					wsh_list->wsh_envs[i + k] = NULL;
				}
			}
			j++;
		}
		i++;
	}
	printf("%s", arr[0]);
	// if (k != 0)
	// 	wsh_free((void **)arr);
	return ;
}