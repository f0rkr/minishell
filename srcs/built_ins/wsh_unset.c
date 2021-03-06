#include "minishell.h"

void	ft_tmparr(char tmp[][1024], char **env, int i)
{
	int		j;
	int 	k;

	j = 0;
	k = i;
	while (env[i++]);
	i = k;
	while (env[i])
	{
		ft_strlcpy(tmp[j++], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	tmp[j]['\0'] = 0;
	return ;
}

void	wsh_unset(t_wsh_tokens *wsh_token, t_wsh_list *wsh_list)
{
	int	i;
	int j;
	char arr[1024][1024];
	char *tmp;
	int k;

	i = 0;
	while (wsh_list->wsh_envs[i] != NULL)
	{
		j = 0;
		while (wsh_token->wsh_param[j] != NULL)
		{
			if (wsh_list->wsh_envs[i] && wsh_token->wsh_param[j] && wsh_list->wsh_envs[i][0] == wsh_token->wsh_param[j][0])
			{
				tmp = before_eq(wsh_token->wsh_param[j]);
				if (!(ft_strncmp(wsh_list->wsh_envs[i], tmp, ft_strlen(tmp))))
				{
					k = 0;
					ft_tmparr(arr, wsh_list->wsh_envs, i + 1);
					while (arr[k][0] != '\0')
					{
						if (wsh_list->wsh_envs[i + k])
						{
							free(wsh_list->wsh_envs[i + k]);
							wsh_list->wsh_envs[i + k] = NULL;
						}
						wsh_list->wsh_envs[i + k] = ft_strdup(arr[k]);
						k++;
					}
					while (wsh_list->wsh_envs[i + k])
					{
						free(wsh_list->wsh_envs[i + k]);
						wsh_list->wsh_envs[i + k] = NULL;
						i++;
						k++;
					}
					wsh_list->wsh_envs[i + k] = NULL;
				}
			}
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
			j++;
		}
		i++;
	}
	return ;
}