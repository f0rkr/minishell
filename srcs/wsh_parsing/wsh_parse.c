/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:25:23 by mashad            #+#    #+#             */
/*   Updated: 2021/04/07 13:14:56 by mashad           ###   ########.fr       */
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

void	wsh_fill_token(t_wsh_list *wsh_list, t_wsh_tokens *wsh_token,
	char string[][1024])
{
	int			c_i;
	char		pipe[1024][1024];
	char		*tmp;

	c_i = 0;
	tmp = NULL;
	wsh_fill_redirection(wsh_token, string);
	wsh_token->wsh_command = wsh_escape(wsh_list, string[c_i++]);
	if (ft_isin(SPACE, wsh_token->wsh_command))
	{
		if (wsh_tokenizer(pipe, wsh_token->wsh_command, 2) == ERROR)
			return ;
		wsh_free(&wsh_token->wsh_command);
		wsh_fill_token(wsh_list, wsh_token, pipe);
	}
	if (ft_isbuiltin(wsh_token->wsh_command))
		wsh_token->type = BUILTIN;
	if (wsh_token->type != BUILTIN && !ft_isubuiltin(wsh_token->wsh_command))
	{
		tmp = wsh_token->wsh_command;
		wsh_token->wsh_command = ft_lowerit(wsh_token->wsh_command);
		free(tmp);
	}
	wsh_fillargs(wsh_list, wsh_token, string, &c_i);
	wsh_fillparams(wsh_token, string, &c_i);
}

void	wsh_command_normalizer(char *str)
{
	char	new_str[1024];
	int		c_i;
	int		c_k;

	c_i = 0;
	c_k = 0;
	while (str[c_i] != EOL)
	{
		if (str[c_i] == SQUOTE || str[c_i] == DQUOTE)
		{
			while (ft_isin(str[c_i], "\'\""))
				new_str[c_k++] = str[c_i++];
			new_str[c_k++] = str[c_i++];
		}
		if ((str[c_i] == '>' || str[c_i] == '<') && !isesc(str, c_i - 1))
			wsh_command_norm(str, new_str, &c_i, &c_k);
		else
			new_str[c_k++] = str[c_i];
		c_i++;
	}
	new_str[c_k] = EOL;
	ft_strlcpy(str, new_str, ft_strlen(new_str) + 1);
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
