#include "parsing.h"

int	ft_isubuiltin(const char *command)
{
	static char		builin[7][10] = {"echo", "cd", "pwd",
		"exit", "export", "unset", "env"};
	int				i;
	char			*str;

	str = ft_lowerit((char *)command);
	i = 0;
	while (ft_strncmp(str, builin[i], ft_strlen(builin[i])) != 0)
		i++;
	free(str);
	str = NULL;
	if (i == 7)
		return (0);
	return (1);
}

int	isesc(char *string, int pos)
{
	int	c_c;

	c_c = 0;
	pos--;
	while (pos >= 0)
	{
		if (string[pos] == ESC)
			c_c++;
		else
			break ;
		pos--;
	}
	if (c_c % 2 != 0)
		return (1);
	return (0);
}

void	wsh_command_norm(char *str, char *new_str, int *c_i, int *c_k)
{
	if (str[*c_i - 1] != SPACE)
		new_str[(*c_k)++] = SPACE;
	new_str[(*c_k)++] = str[*c_i];
	if (str[(*c_i) + 1] == OUTRID)
		new_str[(*c_k)++] = str[++(*c_i)];
	new_str[(*c_k)++] = SPACE;
}

void	wsh_redirection_dup(t_wsh_tokens *wsh_token,
		char string[][1024], int *c_j, int *c_n)
{
	wsh_token->wsh_redi->type = ft_strdup(string[*c_j]);
	ft_strlcpy(string[(*c_j)++], "NULL", 5);
	wsh_token->wsh_redi->filename = ft_strdup(string[*c_j]);
	ft_strlcpy(string[*c_j], "NULL", 5);
	if (*c_n > 1)
	{
		wsh_token->wsh_redi->next = wsh_redi_init();
		wsh_token->wsh_redi = wsh_token->wsh_redi->next;
		(*c_n)--;
	}
}

int	ft_issi(char c)
{
	if (c == V || c == DQUOTE)
		return (1);
	return (0);
}
