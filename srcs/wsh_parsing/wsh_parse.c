/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:25:23 by mashad            #+#    #+#             */
/*   Updated: 2021/03/26 17:46:02 by oel-ouar         ###   ########.fr       */
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
	while (wsh_args[*position][0] == '-' && wsh_args[*position][0] != EOL)
	{	
		wsh_escape(envs, wsh_args[*position]);
		wsh_token->wsh_arg[counter++] = ft_strdup(wsh_args[(*position)++]);
	}
	if (wsh_args[*position][0] == '-' && wsh_args[*position][0] != EOL)
	{
		wsh_escape(envs, wsh_args[*position]);
		wsh_token->wsh_arg[counter++] = ft_strdup(wsh_args[(*position)++]);
	}
	wsh_token->wsh_arg[counter] = 0;
	return (NULL);
}

int		g_count;

int		wsh_fillparams(t_wsh_tokens *wsh_token, char *wsh_params)
{
	if (g_count == 0)
	{
		wsh_token->wsh_param = (char **)malloc(sizeof(char *) * 1024);
		if (!wsh_token->wsh_param)
			return (EXIT);
	}
	if (wsh_params && !wsh_is_redirection(wsh_params))
		wsh_token->wsh_param[g_count++] = ft_strdup(wsh_params);
	wsh_token->wsh_param[g_count] = 0;
	return (EXIT);
}

void	wsh_fill_token(char **envs, t_wsh_tokens *wsh_token, char string[][1024])
{
	int			c_i;
	int			c_j;
	t_wsh_redi	*wsh_redi;

	
	c_i = 0;
	c_j = 0;
	g_count = 0;
	wsh_redi = NULL;
	if (wsh_is_redirection((string[c_i])))
	{
		if (c_j++ == 0)
		{
			wsh_token->wsh_redi = wsh_redi_init();
			if (c_j++ == 0 && !(wsh_token->wsh_redi))
				return ;
			wsh_redi = wsh_token->wsh_redi;
		}
		wsh_fill_redirection(wsh_token, string, &c_i);
	}
	wsh_token->wsh_command = ft_strdup(string[c_i++]);
	if (ft_isbuiltin(wsh_token->wsh_command))
		wsh_token->type = BUILTIN;
	if (!wsh_is_redirection(string[c_i]))
		wsh_fillargs(envs, wsh_token, string, &c_i);
	while (string[c_i][0] != EOL)
	{
		if (wsh_is_redirection(string[c_i]))
		{
			if (c_j++ == 0)
			{
				wsh_token->wsh_redi = wsh_redi_init();
				if (c_j++ == 0 && !(wsh_token->wsh_redi))
					return ;
				wsh_redi = wsh_token->wsh_redi;
			}
			wsh_token->wsh_redi->type = ft_strdup(string[c_i++]);
			wsh_token->wsh_redi->filename = ft_strdup(string[c_i]);
			if (wsh_is_redirection((string[c_i + 1])))
			{
				wsh_token->wsh_redi->next = wsh_redi_init();
				wsh_token->wsh_redi = wsh_token->wsh_redi->next;
			}
		}
		else if (string[c_i][0] != EOL)
			wsh_fillparams(wsh_token, string[c_i]);
		c_i++;
	}

	wsh_token->wsh_redi = wsh_redi;
	return ;
}

void		wsh_command_normalize(char *string)
{
	char	new_str[1024];
	int		c_i;
	int		c_k;

	c_i = 0;
	c_k = 0;
	while (string[c_i] != EOL)
	{
		if (string[c_i] == OUTRID || string[c_i] == INRID)
		{
			new_str[c_k++] = string[c_i];
			if (string[c_i + 1] == OUTRID)
				new_str[c_k++] = string[++c_i];
			new_str[c_k++] = SPACE;
		}
		else
		{
			new_str[c_k++] = string[c_i];
			if (string[c_i + 1] == OUTRID || string[c_i + 1] == INRID)
				new_str[c_k++] = SPACE;
		}
		c_i++;
	}
	new_str[c_k] = EOL;
	ft_strlcpy(string, new_str, ft_strlen(new_str) + 1);
	return ;
}

t_wsh_tokens	*wsh_fillCommands(char **envs, t_wsh_tokens *wsh_token, char pipe[][1024])
{
	int		counter;
	char	foreach[1024][1024];

	counter = 0;
	while (pipe[counter][0] != EOL)
	{
		wsh_command_normalize(pipe[counter]);
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
