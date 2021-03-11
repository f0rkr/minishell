#include "minishell.h"

int		searcheq(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && i != 0)
			return (1);
		i++;
	}
	return (0);
}

char	*before_eq(char *str)
{
	int		i;
	char	*ret;
	int		j;

	i = 0;
	j = 0;
	if (!(ret = malloc(sizeof(char *) * 1024)))
		return (NULL);
	while (str[i])
	{
		ret[j] = str[i];
		if (str[i] == '=')
		{
			if (str[i - 1]== ' ')
				return (NULL);
			break;
		}
		i++;
		j++;
	}
	return (ret);
}

void	wsh_export(t_wsh_tokens *wsh_token,
t_wsh_list *wsh_list)
{
	char	*temp;
	char	*str;
	int		i;
	int 	j;
	int		cond;

	i = 0;
	j = 1;
	cond = 0;
	if (!(temp = (char *)malloc(sizeof(char) * 4029)))
		return ;
	while (wsh_token->wsh_param[i])
	{
		j = i + 1;
		while (wsh_token->wsh_param[i] && wsh_token->wsh_param[j] && i != j)
		{
			str = before_eq(wsh_token->wsh_param[i]);
			if (ft_strncmp(wsh_token->wsh_param[i], wsh_token->wsh_param[j], ft_strlen(str)) == 0)
				ft_strlcpy(wsh_token->wsh_param[i], "NAN", 4);
			if (str)
				wsh_free((void *)str);
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	wsh_unset(wsh_token, wsh_list);
	while (wsh_list->wsh_envs[i++]);
	i--;
	while (wsh_token->wsh_param[j] != NULL)
	{
		if (searcheq(wsh_token->wsh_param[j]))
			wsh_list->wsh_envs[i++] = ft_strdup(wsh_token->wsh_param[j]);
		j++;
	}
	return ;
}
