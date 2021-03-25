#include "parsing.h"

void	wsh_replacevar(char **envs, char pipe[1024], int c_pos)
{
	char	var[1024];
	char	*c_var;
	int		c_i;
	int		c_j;
	int		c_k;

	c_j = c_pos++;
	c_i = 0;
	c_k = 0;
	if (pipe[c_pos] == EOL || (!ft_isspecial(pipe, c_pos) && !ft_isalnum(pipe[c_pos])))
		return ;
	if (ft_isspecial(pipe, c_pos))
		var[c_i++] = pipe[c_pos++];
	else
		while (pipe[c_pos] != EOL && (ft_isalnum(pipe[c_pos])
				|| pipe[c_pos] == '_'))
			var[c_i++] = pipe[c_pos++];
	var[c_i] = EOL;
	c_var = ft_strdup(wsh_get_envar((char *)var, envs));
	c_i = 0;
	while (pipe[c_i] != EOL && pipe[c_i] != VAR)
		var[c_k++] = pipe[c_i++];
	c_i = 0;
	while (c_var && c_var[c_i] != EOL)
		var[c_k++] = c_var[c_i++];
	while (pipe[c_pos] != EOL)
		var[c_k++] = pipe[c_pos++];
	var[c_k] = EOL;
	return ((void) ft_strlcpy(pipe, var, ft_strlen(var) + 1));
}

void	wsh_escape(char **envs, char pipe[1024])
{
	int		c_i;
	int		c_j;
	int		c_sq;
	int		c_dq;
	int		c_p;
	char	newpipe[1024];

	c_sq = 0;
	c_dq = 0;
	c_p = 0;
	c_i = 0;
	c_j = 0;
	while (pipe[c_i] != EOL)
	{
		if (c_p == 0 && c_dq == 0 && c_sq == 0 && pipe[c_i] == SQUOTE)
			c_sq = 1;
		else if (c_sq == 1 && pipe[c_i] == SQUOTE)
			c_sq = 0;
		if (c_p == 0 && c_sq == 0 && c_dq == 0 && pipe[c_i] == DQUOTE)
			c_dq = 1;
		else if (c_dq == 1 && pipe[c_i] == DQUOTE)
			c_dq = 0;
		if (c_p == 0 && c_sq == 0 && pipe[c_i] == VAR && pipe[c_i + 1] != EOL)
		{
			wsh_replacevar(envs, pipe, c_i);
			wsh_escape(envs, pipe);
		}
		if (c_p == 0 && c_sq == 0 && pipe[c_i] == ESC)
			c_p = 1;
		else if (c_p == 1 && c_sq == 0)
			c_p = 0;
		if (wsh_quotesremove(&pipe[c_i - 1], c_sq, c_dq, c_p))
			newpipe[c_j++] = pipe[c_i];
		if (pipe[c_i] == EOL)
			break ;
		c_i++;
	}
	newpipe[c_j] = EOL;
	return ((void) ft_strlcpy(pipe, newpipe, ft_strlen(newpipe) + 1));
}

void	wsh_stick_redi(t_wsh_tokens *wsh_token, char *string)
{
	int		c_i;
	int		c_j;
	char	type[2];
	char	filename[1024];

	c_i = 0;
	while (string[c_i] != EOL)
	{
		c_j = 0;
		while ((string[c_i] == OUTRID || string[c_i] == INRID) && string[c_i] != EOL)
			type[c_j++] = string[c_i++];
		type[c_i] = EOL;
		c_j = 0;
		while ((string[c_i] != OUTRID && string[c_i] != INRID) && string[c_i] != EOL)
			filename[c_j++] = string[c_i++];
		filename[c_j] = EOL;
		wsh_token->wsh_redi->type = ft_strdup(type);
		wsh_token->wsh_redi->filename = ft_strdup(filename);
		if ((string[c_i] == OUTRID || string[c_i] == INRID) && string[c_i] != EOL)
		{
			wsh_token->wsh_redi->next = wsh_redi_init();
			wsh_token->wsh_redi = wsh_token->wsh_redi->next;
		}
	}
	return ;
}

void	wsh_fill_redirection(t_wsh_tokens *wsh_token, char redi[][1024], int *c_i)
{
	t_wsh_redi	*wsh_red;

	wsh_red = wsh_token->wsh_redi;
	while (redi[(*c_i)] != EOL && wsh_is_redirection(redi[(*c_i)]))
	{
		wsh_token->wsh_redi->type = ft_strdup(redi[(*c_i)++]);
		wsh_token->wsh_redi->filename = ft_strdup(redi[(*c_i)]);
		wsh_token->wsh_redi->next = wsh_redi_init();
		wsh_token->wsh_redi = wsh_token->wsh_redi->next;
		(*c_i)++;
	}
	wsh_token->wsh_redi = wsh_red;
}
