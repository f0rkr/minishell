#include "parsing.h"

extern int	ft_isspecial(char c)
{
	if (c == '_' || c == '#'
		|| c == '$' || c == '-'
		|| c == '?')
		return (1);
	return (0);
}

extern int	wsh_is_redirection(char *c_r)
{
	if (ft_strncmp(c_r, ">>", 2) == 0)
		return (1);
	else if (ft_strncmp(c_r, "<", 1) == 0 || ft_strncmp(c_r, ">", 1) == 0)
		return (1);
	return (0);
}

int	wsh_is_closed(char *string, int pos, char c)
{
	while (string[pos] != EOL)
	{
		if (string[pos] == SQUOTE)
			break ;
		if (string[pos] == c && !isesc(string, pos))
			break ;
		pos++;
	}
	if (string[pos] == SQUOTE)
		return (1);
	else if (string[pos] == DQUOTE && !isesc(string, pos))
		return (1);
	return (0);
}

void	wsh_remove_pointer(char string[][1024], char *str)
{
	int		c_i;
	int		c_j;
	char	tmp[1024][1024];

	c_i = 0;
	c_j = 0;
	while (string[c_i][0] != EOL)
	{
		if (ft_strncmp(string[c_i], str, ft_strlen(str)) != 0)
			ft_strlcpy(tmp[c_j++], string[c_i], ft_strlen(string[c_i]) + 1);
		c_i++;
	}
	c_i = 0;
	tmp[c_j][0] = EOL;
	while (tmp[c_i][0] != EOL)
	{
		ft_strlcpy(string[c_i], tmp[c_i], ft_strlen(tmp[c_i]) + 1);
		c_i++;
	}
	string[c_i][0] = EOL;
}

void	wsh_process_quotes(t_wsh_list *l, char new[1024], int *pos, int *c_j)
{
	if (l->tmp[*pos] == SQUOTE)
		wsh_read_squote(l, new, pos, c_j);
	else if (l->tmp[*pos] == DQUOTE)
		wsh_read_dquote(l, new, pos, c_j);
	(*pos)++;
	return ;
}
