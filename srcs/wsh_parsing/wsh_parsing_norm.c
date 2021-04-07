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

int	wsh_isescape(char *string, int pos)
{
	int	c_c;

	c_c = 0;
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
