#include "parsing.h"

void	wsh_read_dquote_help(t_wsh_list *l, int *pos, int c_i)
{
	char	*line;

	line = NULL;
	if (!wsh_is_closed(l->tmp, *pos, DQUOTE))
	{
		l->garbage_flag = STDIN;
		while (!wsh_is_closed(l->tmp, *pos, DQUOTE))
		{
			line = wsh_read(l, &l->garbage_flag);
			line = ft_strjoin("\n", line);
			line = ft_strjoin(l->tmp, line);
			ft_strlcpy(l->tmp, line, ft_strlen(line) + 1);
			free(line);
		}
		l->garbage_flag = c_i;
	}
}

void	wsh_esc_help(t_wsh_list *l, char *newpipe, int *c_j, int i)
{
	int	c_escape;

	c_escape = 0;
	while (l->tmp[i] != EOL)
	{
		if (ft_isin(l->tmp[i], "\'\"") && !isesc(l->tmp, i))
		{
			wsh_process_quotes(l, newpipe, &i, c_j);
			continue ;
		}
		else if (l->tmp[i] == V && !isesc(l->tmp, i) && l->tmp[i + 1] != EOL
			&& (ft_isalpha(l->tmp[i + 1]) || ft_isspecial(l->tmp[i + 1])))
		{
			wsh_replacevar(l, newpipe, &i, c_j);
			continue ;
		}
		if (l->tmp[i] == ESC && !ft_issi(l->tmp[i]) && c_escape == 0)
			c_escape = 1;
		else if (c_escape == 1)
			c_escape = 0;
		if (c_escape == 0)
			newpipe[(*c_j)++] = l->tmp[i];
		i++;
	}
}

int	wsh_scan_help(char *str, int c_c, int q[2], int flag)
{
	if (ft_isin(str[c_c], "\"") && !isesc((char *)str, c_c) && q[0] == 0 && flag == 0)
		return (1);
	else if (ft_isin(str[c_c], "\"") && !isesc((char *)str, c_c) && q[0] == 1 && flag == 0)
		return (0);
	if (ft_isin(str[c_c], "\'") && !isesc((char *)str, c_c) && q[1] == 0 && flag == 1)
		return (1);
	else if (ft_isin(str[c_c], "\'") && !isesc((char *)str, c_c) && q[1] == 1 && flag == 1)
		return (0);
	if (flag == 0)
		return (q[0]);
	return (q[1]);
}

void	wsh_cd_home(char *tmp)
{
	char	*tmp1;

	tmp1 = tmp;
	wsh_free(&tmp);
	tmp = ft_strjoin(tmp1, "/");
	chdir(tmp);
	wsh_free(&tmp);
	wsh_free(&tmp1);
}

int	string_checker(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == PIPE || string[i] == AND)
			break ;
		i++;
	}
	if (string[i] == PIPE || string[i] == AND)
	{
		i++;
		while (string[i] == SPACE)
			i++;
		if (string[i] == PIPE || string[i] == AND)
		{
			ft_putstr_fd("wsh: syntax error near unexpected token `", 2);
			ft_putchar_fd(string[i], 2);
			ft_putendl_fd("'", 2);
			g_tab[0] = 258;
			return (0);
		}
	}
	return (1);
}
