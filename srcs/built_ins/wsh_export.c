#include "minishell.h"


int		wsh_strcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (dst == NULL || src == NULL)
		return (0);
	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (ft_strlen(src) == 0)
	{
		*dst = '\0';
		return (0);
	}
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

size_t		ft_strle(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n] != '\0')
		n++;
	return (n);
}


void	wsh_export(t_wsh_tokens *wsh_token,
t_wsh_list *wsh_list)
{
	char	*temp;
	int		i;
	int 	j;

	i = 0;
	j = 0;
	temp = (char *)ft_malloc(sizeof(char) * 4029);
	while (wsh_list->wsh_envs[i++]);
	i-=2;
	ft_strlcpy(temp, wsh_list->wsh_envs[i], ft_strle(wsh_list->wsh_envs[i])+1);
	while (wsh_token->wsh_param[j][0] != '\0')
	{
		wsh_list->wsh_envs[i++] = ft_strdup(wsh_token->wsh_param[j]);
		j++;
	}
	wsh_list->wsh_envs[i++] = ft_strdup(temp);
	return ;
}