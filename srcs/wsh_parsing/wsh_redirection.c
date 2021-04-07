#include "parsing.h"

void	wsh_replacevar(t_wsh_list *l,
		char newstring[1024], int *c_pos, int *c_j)
{
	char	*var;
	char	*c_var;
	int		c_i;

	(*c_pos)++;
	c_i = 0;
	var = (char *)malloc(sizeof(char) * 4029);
	if (l->tmp[*c_pos] == EOL)
		return ;
	if (ft_isspecial(l->tmp[*c_pos]))
		var[c_i++] = l->tmp[(*c_pos)++];
	else
		while (l->tmp[*c_pos] != EOL
			&& ft_isalpha(l->tmp[*c_pos]))
			var[c_i++] = l->tmp[(*c_pos)++];
	var[c_i] = EOL;
	c_var = wsh_get_envar((char *)var, l->wsh_envs);
	c_i = 0;
	ft_strlcpy(&newstring[*c_j], c_var, ft_strlen(c_var) + 1);
	*c_j = *c_j + ft_strlen(c_var);
	wsh_free(&var);
	wsh_free(&c_var);
	return ;
}

void	wsh_read_squote(t_wsh_list *l,
		char newstring[1024], int *pos, int *c_j)
{
	char	*line;
	int		c_i;

	line = NULL;
	c_i = l->garbage_flag;
	(*pos)++;
	if (wsh_is_closed(l->tmp, *pos, SQUOTE) == 0)
	{
		l->garbage_flag = STDIN;
		while (!wsh_is_closed(l->tmp, *pos, SQUOTE))
		{
			line = wsh_read(l, &l->garbage_flag);
			line = ft_strjoin("\n", line);
			line = ft_strjoin(l->tmp, line);
			ft_strlcpy(l->tmp, line, ft_strlen(line) + 1);
			free(line);
		}
		l->garbage_flag = c_i;
	}
	while (l->tmp[*pos] != SQUOTE)
		newstring[(*c_j)++] = l->tmp[(*pos)++];
	return ;
}

void	wsh_read_dquote(t_wsh_list *l,
		char newstring[1024], int *pos, int *c_j)
{
	int		c_escape;
	int		c_i;

	c_i = l->garbage_flag;
	c_escape = 0;
	(*pos)++;
	wsh_read_dquote_help(l, pos, c_i);
	while (l->tmp[*pos] != '\"' || (l->tmp[*pos] == '\"' && isesc(l->tmp, *pos)))
	{
		if (l->tmp[*pos] == V && !isesc(l->tmp, *pos) && l->tmp[*pos + 1] != EOL
			&& (ft_isalpha(l->tmp[*pos + 1]) || ft_isspecial(l->tmp[*pos + 1])))
		{
			wsh_replacevar(l, newstring, pos, c_j);
			continue ;
		}
		if (l->tmp[*pos] == ESC && ft_issi(l->tmp[*pos + 1]) && c_escape == 0)
			c_escape = 1;
		else if (c_escape == 1)
			c_escape = 0;
		if (c_escape == 0)
			newstring[(*c_j)++] = l->tmp[*pos];
		(*pos)++;
	}
}

char	*wsh_escape(t_wsh_list *wsh_list, char *pipe)
{
	int		c_j;
	int		i;
	char	*newpipe;

	i = 0;
	c_j = 0;
	wsh_list->tmp = pipe;
	newpipe = (char *)malloc(sizeof(char) * 4029);
	wsh_esc_help(wsh_list, newpipe, &c_j, i);
	newpipe[c_j] = EOL;
	return (newpipe);
}

void	wsh_fill_redirection(t_wsh_tokens *wsh_token, char string[][1024])
{
	int			c_i;
	int			c_j;
	int			c_n;
	t_wsh_redi	*wsh_redi;

	c_i = 0;
	c_j = 0;
	c_n = 0;
	wsh_redi = NULL;
	while (string[c_i][0] != EOL)
		if (wsh_is_redirection(string[c_i++]))
			c_n++;
	if (c_n == 0)
		return ;
	wsh_token->wsh_redi = wsh_redi_init();
	wsh_redi = wsh_token->wsh_redi;
	while (string[c_j][0] != EOL)
	{
		if (wsh_is_redirection(string[c_j]) && string[c_j + 1] != EOL)
			wsh_redirection_dup(wsh_token, string, &c_j, &c_n);
		c_j++;
	}
	wsh_remove_pointer(string, "NULL");
	wsh_token->wsh_redi = wsh_redi;
}
