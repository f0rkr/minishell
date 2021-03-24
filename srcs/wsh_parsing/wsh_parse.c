/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:25:23 by mashad            #+#    #+#             */
/*   Updated: 2021/03/24 17:24:50 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*wsh_fillargs(char **envs, t_wsh_tokens *wsh_token, char wsh_args[][1024], int *position)
{
	int		counter;

	counter = 0;
	if (!wsh_token->wsh_arg)
		return (NULL);
	wsh_token->wsh_arg = (char **)malloc(sizeof(char *) * 1024);
	if (wsh_args[*position][0] != '-')
		return (NULL);
	while (wsh_args[*position][0] == '-' && wsh_args[*position][0] != '\0')
	{	
		wsh_escape(envs, wsh_args[*position]);
		wsh_token->wsh_arg[counter++] = ft_strdup(wsh_args[(*position)++]);
	}
	if (wsh_args[*position][0] == '-' && wsh_args[*position][0] != '\0')
	{
		wsh_escape(envs, wsh_args[*position]);
		wsh_token->wsh_arg[counter++] = ft_strdup(wsh_args[(*position)++]);
	}
	wsh_token->wsh_arg[counter] = 0;
	return (NULL);
}

int		g_count;

void	*wsh_fillparams(t_wsh_tokens *wsh_token, char wsh_params[][1024], int *position)
{
	if (wsh_params[*position][0] == '\0')
		return (NULL);
	if (g_count == 0)
	{
		wsh_token->wsh_param = (char **)malloc(sizeof(char *) * 1024);
		if (!wsh_token->wsh_param)
			return (NULL);
	}
	while (wsh_params[*position][0] != '\0' && !wsh_is_redirection(wsh_params[*position]))
		wsh_token->wsh_param[g_count++] = ft_strdup(wsh_params[(*position)++]);
	if (wsh_params[*position] && wsh_params[*position][0] != '\0' && !wsh_is_redirection(wsh_params[*position]))
		wsh_token->wsh_param[g_count++] = ft_strdup(wsh_params[(*position)++]);
	wsh_token->wsh_param[g_count] = 0;
	return (NULL);
}

void	wsh_fill_token(char **envs, t_wsh_tokens *wsh_token, char string[][1024])
{
	int		c_i;

	c_i = 0;
	g_count = 0;
	if (wsh_is_redirection((string[c_i])))
		wsh_fill_redirection(wsh_token, string, &c_i);
	wsh_token->wsh_command = ft_strdup(string[c_i++]);
	if (ft_isbuiltin(wsh_token->wsh_command))
		wsh_token->type = BUILTIN;
	if (!wsh_is_redirection(wsh_token->wsh_command))
		wsh_fillargs(envs, wsh_token, string, &c_i);
	wsh_fillparams(wsh_token, string, &c_i);
	if (wsh_is_redirection(string[c_i]))
		wsh_fill_redirection(wsh_token, string, &c_i);
	wsh_fillparams(wsh_token, string, &c_i);
	return ;
}

t_wsh_tokens	*wsh_fillCommands(char **envs, t_wsh_tokens *wsh_token, char pipe[][1024])
{
	int		counter;
	char	foreach[1024][1024];

	counter = 0;
	while (pipe[counter][0] != EOL)
	{
		if (wsh_tokenizer(foreach, pipe[counter], 2) == ERROR)
			return (NULL);
		wsh_fill_token(envs, wsh_token, foreach);
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

t_wsh_tokens	*wsh_parse(char **envs, char *cmd)
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
		wsh_token = wsh_fillCommands(envs, wsh_token, pipe);
		if (array[++i][0] != EOL)
		{
			wsh_token->next = wsh_token_init();
			wsh_token = wsh_token->next;
		}
	}
	return (wsh_token_first);
}
