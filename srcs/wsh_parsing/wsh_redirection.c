#include "parsing.h"

void	wsh_replacevar(char **envs, char newstring[1024],
		char string[1024], int *c_pos, int *c_j)
{
	char	*var;
	char	*c_var;
	int		c_i;

	(*c_pos)++;
	c_i = 0;
	var = (char *)malloc(sizeof(char) * 4029);
	if (string[*c_pos] == EOL)
		return ;
	while (string[*c_pos] != EOL
		&& (ft_isspecial(string[*c_pos]) || ft_isalpha(string[*c_pos])))
		var[c_i++] = string[(*c_pos)++];
	var[c_i] = EOL;
	c_var = wsh_get_envar((char *)var, envs);
	c_i = 0;
	ft_strlcpy(&newstring[*c_j], c_var, ft_strlen(c_var) + 1);
	*c_j = *c_j + ft_strlen(c_var) + 1;
	wsh_free(&var);
	wsh_free(&c_var);
	return ;
}

int	ft_issi(char c)
{
	if (c == VAR || c == DQUOTE)
		return (1);
	return (0);
}

int	is_escape(char *string, int pos)
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

int	wsh_is_closed(char *string, int pos, char c)
{
	while (string[pos] != EOL)
	{
		if (string[pos] == SQUOTE)
			break ;
		if (string[pos] == c && !is_escape(string, pos))
			break ;
		pos++;
	}
	if (string[pos] == SQUOTE)
		return (1);
	else if (string[pos] == DQUOTE && !is_escape(string, pos))
		return (1);
	return (0);
}

void	wsh_read_squote(t_wsh_list *wsh_list,
		char newstring[1024], char string[1024], int *pos, int *c_j)
{
	char	*line;
	int		c_i;

	line = NULL;
	c_i = wsh_list->garbage_flag;
	(*pos)++;
	if (wsh_is_closed(string, *pos, SQUOTE) == 0)
	{
		wsh_list->garbage_flag = STDIN;
		while (!wsh_is_closed(string, *pos, SQUOTE))
		{
			line = wsh_read(wsh_list, &wsh_list->garbage_flag);
			line = ft_strjoin("\n", line);
			line = ft_strjoin(string, line);
			ft_strlcpy(string, line, ft_strlen(line) + 1);
			free(line);
		}
		wsh_list->garbage_flag = c_i;
	}
	while (string[*pos] != SQUOTE)
		newstring[(*c_j)++] = string[(*pos)++];
	return ;
}

void	wsh_read_dquote(t_wsh_list *wsh_list, char newstring[1024], char string[1024], int *pos, int *c_j)
{
	int		c_escape;
	char	*line;
	int		c_i;

	c_i = wsh_list->garbage_flag;
	line = NULL;
	c_escape = 0;
	(*pos)++;
	if (!wsh_is_closed(string, *pos, DQUOTE))
	{
		wsh_list->garbage_flag = STDIN;
		while (!wsh_is_closed(string, *pos, DQUOTE))
		{
			line = wsh_read(wsh_list, &wsh_list->garbage_flag);
			line = ft_strjoin("\n", line);
			line = ft_strjoin(string, line);
			ft_strlcpy(string, line, ft_strlen(line) + 1);
			free(line);
		}
		wsh_list->garbage_flag = c_i;
	}
	while (string[*pos] != DQUOTE || (string[*pos] == DQUOTE && is_escape(string, *pos)))
	{
		if (string[*pos] == VAR && !is_escape(string, *pos) && string[*pos + 1] != EOL && (ft_isalpha(string[*pos + 1]) || ft_isspecial(string[*pos + 1])))
		{
			wsh_replacevar(wsh_list->wsh_envs, newstring, string, pos, c_j);
			continue;
		}
		if (string[*pos] == ESC && ft_issi(string[*pos]) && c_escape == 0)
			c_escape = 1;
		else if (c_escape == 1)
			c_escape = 0;
		if (c_escape == 0)
			newstring[(*c_j)++] = string[*pos];
		(*pos)++;
	}
}

void	wsh_process_quotes(t_wsh_list *wsh_list, char newstring[1024], char string[1024], int *pos, int *c_j)
{
	if (string[*pos] == SQUOTE)
		wsh_read_squote(wsh_list, newstring, string, pos, c_j);
	else if (string[*pos] == DQUOTE)
		wsh_read_dquote(wsh_list, newstring, string, pos, c_j);
	(*pos)++;
	return ;
}

char	*wsh_escape(t_wsh_list *wsh_list, char *pipe)
{
	int		c_i;
	int		c_j;
	int		c_escape;
	char	*newpipe;

	c_i = 0;
	c_j = 0;
	c_escape = 0;
	newpipe = (char *)malloc(sizeof(char) * 4029);
	while (pipe[c_i] != EOL)
	{
		if (ft_isin(pipe[c_i], "\'\"") && !is_escape(pipe, c_i))
		{
			wsh_process_quotes(wsh_list, newpipe, pipe, &c_i, &c_j);
			continue;
		}
		else if (pipe[c_i] == VAR && !is_escape(pipe, c_i) && pipe[c_i + 1] != EOL && (ft_isalpha(pipe[c_i + 1]) || ft_isspecial(pipe[c_i + 1])))
		{
			wsh_replacevar(wsh_list->wsh_envs, newpipe, pipe, &c_i, &c_j);
			continue;
		}
		if (pipe[c_i] == ESC && !ft_issi(pipe[c_i]) && c_escape == 0)
			c_escape = 1;
		else if (c_escape == 1)
			c_escape = 0;
		if (c_escape == 0)
			newpipe[c_j++] = pipe[c_i];
		c_i++;
	}
	newpipe[c_j] = EOL;
	return (newpipe);
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
	{
		if (wsh_is_redirection(string[c_i]))
			c_n++;
		c_i++;
	}
	if (c_n == 0)
		return ;
	wsh_token->wsh_redi = wsh_redi_init();
	wsh_redi = wsh_token->wsh_redi;
	while (string[c_j][0] != EOL)
	{
		if (wsh_is_redirection(string[c_j]) && string[c_j + 1] != EOL)
		{
			wsh_token->wsh_redi->type = ft_strdup(string[c_j]);
			ft_strlcpy(string[c_j++], "NULL", 5);
			wsh_token->wsh_redi->filename = ft_strdup(string[c_j]);
			ft_strlcpy(string[c_j], "NULL", 5);
			if (c_n > 1)
			{
				wsh_token->wsh_redi->next = wsh_redi_init();
				 wsh_token->wsh_redi = wsh_token->wsh_redi->next;
				c_n--;
			}
		}
		c_j++;
	}
	wsh_remove_pointer(string, "NULL");
	wsh_token->wsh_redi = wsh_redi;
}