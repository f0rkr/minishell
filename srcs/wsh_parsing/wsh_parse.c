/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:25:23 by mashad            #+#    #+#             */
/*   Updated: 2021/03/29 09:53:40 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	wsh_fillparams(t_wsh_tokens *wsh_token, char string[][1024], int *pos)
{
	int	c_i;

	c_i = 0;
	if (string[*pos][0] == EOL)
		return (EXIT);
	wsh_token->wsh_param = (char **)malloc(sizeof(char *) * 1024);
	if (!wsh_token->wsh_param)
		return (EXIT);
	while (string[*pos][0] != EOL)
		wsh_token->wsh_param[c_i++] = ft_strdup(string[(*pos)++]);
	wsh_token->wsh_param[c_i] = 0;
	return (EXIT);
}

void	ft_lowerit(char string[][1024], int c_i)
{
	int c_j;

	c_j = 0;
	while (string[c_i][c_j] != EOL)
	{
		string[c_i][c_j] = ft_tolower(string[c_i][c_j]);
		c_j++;
	}
	return ;
}

void	wsh_fill_token(t_wsh_list *wsh_list, t_wsh_tokens *wsh_token,
	char string[][1024])
{
	int			c_i;
	char		pipe[1024][1024];

	c_i = 0;
	wsh_fill_redirection(wsh_token, string);
	wsh_escape(wsh_list, string[c_i]);
	wsh_token->wsh_command = ft_strdup(string[c_i++]);
	if (ft_isin(SPACE, wsh_token->wsh_command))
	{
		if (wsh_tokenizer(pipe, wsh_token->wsh_command, 2) == ERROR)
			return ;
		wsh_fill_token(wsh_list, wsh_token, pipe);
	}
	if (ft_isbuiltin(wsh_token->wsh_command))
		wsh_token->type = BUILTIN;
	wsh_fillargs(wsh_list, wsh_token, string, &c_i);
	wsh_fillparams(wsh_token, string, &c_i);
}

int		wsh_isescape(char *string, int pos)
{
	int	c_c;

	c_c = 0;
	while (pos >= 0)
	{
		if (string[pos] == ESC)
			c_c++;
		else
			break;
		pos--;
	}
	if (c_c % 2 != 0)
		return (1);
	return (0);
}

void	wsh_command_normalizer(char *string)
{
	char	new_str[1024];
	int		c_i;
	int		c_k;

	c_i = 0;
	c_k = 0;
	while (string[c_i] != EOL)
	{
		if (string[c_i] == SQUOTE || string[c_i] == DQUOTE)
		{
			while (ft_isin(string[c_i], "\'\""))
				new_str[c_k++] = string[c_i++];
			new_str[c_k++] = string[c_i++];
		}
		if ((string[c_i] == OUTRID || string[c_i] == INRID) && !wsh_isescape(string, c_i - 1))
		{
			if (string[c_i - 1] != SPACE)
				new_str[c_k++] = SPACE;
			new_str[c_k++] = string[c_i];
			if (string[c_i + 1] == OUTRID)
				new_str[c_k++] = string[++c_i];
			new_str[c_k++] = SPACE;
		}
		else
			new_str[c_k++] = string[c_i];
		c_i++;
	}
	new_str[c_k] = EOL;
	ft_strlcpy(string, new_str, ft_strlen(new_str) + 1);
	return ;
}

t_wsh_tokens	*wsh_fillCommands(t_wsh_list *wsh_list, t_wsh_tokens *wsh_token
	, char pipe[][1024])
{
	int		counter;
	char	foreach[1024][1024];

	counter = 0;
	while (pipe[counter][0] != EOL)
	{
		wsh_command_normalizer(pipe[counter]);
		if (wsh_tokenizer(foreach, pipe[counter], 2) == ERROR)
			return (NULL);
		wsh_fill_token(wsh_list, wsh_token, foreach);
		if (pipe[++counter][0] != EOL)
		{
			wsh_token->next = wsh_token_init();
			if (!wsh_token->next)
				return (NULL);
			wsh_token->std_out = 666;
			wsh_token = wsh_token->next;
		}
	}
	return (wsh_token);
}

t_wsh_tokens	*wsh_parse(t_wsh_list *wsh_list, char *cmd)
{
	char			array[1024][1024];
	char			pipe[1024][1024];
	t_wsh_tokens	*wsh_token;
	t_wsh_tokens	*wsh_token_first;
	int				i;

	i = 0;
	wsh_token = wsh_token_init();
	if (wsh_tokenizer(array, cmd, 0) == ERROR)
		return (NULL);
	wsh_token_first = wsh_token;
	while (array[i][0] != EOL)
	{
		if (wsh_tokenizer(pipe, array[i], 1) == ERROR)
			return (NULL);
		wsh_token->std_in = 0;
		wsh_token = wsh_fillCommands(wsh_list, wsh_token, pipe);
		if (array[++i][0] != EOL)
		{
			wsh_token->next = wsh_token_init();
			wsh_token = wsh_token->next;
		}
	}
	return (wsh_token_first);
}
