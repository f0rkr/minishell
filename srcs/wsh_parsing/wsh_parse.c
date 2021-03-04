/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:25:23 by mashad            #+#    #+#             */
/*   Updated: 2021/02/26 16:20:04 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		wsh_tokenizer(char cmd[][50], char *string, int pipe)
{
	char    *token;
	int		i;

	i = 0;
	if (!(token = (char *)malloc(sizeof(char) * 50)))
		return (ERROR);
	while (wsh_scan_commands(token, (const char *) string, pipe))
		ft_strlcpy((char *)cmd[i++], (const char *)token, ft_strlen(token)+1);
	ft_strlcpy((char *)cmd[i++], (const char *)token, ft_strlen(token)+1);
	cmd[i][0]= 0;
	free(token);
	token = NULL;
	return (1);
}

void			*wsh_fillargs(t_wsh_tokens *wsh_token, char wsh_args[][50], int *position)
{
	int		counter;

	counter = 0;
	if (wsh_args[*position][0] != '-')
		return (NULL);
	if (!(wsh_token->wsh_arg = (char **)malloc(sizeof(char *) * 100)))
		return (NULL);
	while (wsh_args[*position][0] == '-' && wsh_args[*position][1] != '\0')
		wsh_token->wsh_arg[counter++] = ft_strdup(wsh_args[(*position)++]);
	return (NULL);
}

void			*wsh_fillparams(t_wsh_tokens *wsh_token, char wsh_params[][50], int *position)
{
	int		counter;

	counter = 0;
	if (wsh_params[*position][0] == '\0')
		return (NULL);
	if (!(wsh_token->wsh_param = (char **)malloc(sizeof(char *) * 100)))
		return (NULL);
	while (wsh_params[*position][0] != '\0')
		wsh_token->wsh_param[counter++] = ft_strdup(wsh_params[(*position)++]);
	return (NULL);
}

t_wsh_tokens	*wsh_fillCommands(t_wsh_tokens *wsh_token, char pipe[][50])
{
	int		counter;
	int		i;
	char	foreach[50][50];
	int		j;

	i = 0;
	j = 0;
	while (i < 50)
		ft_memset(foreach[i++], '\0', 50);
	i = 0;
	counter = 0;
	while (pipe[counter][0] != '\0')
	{
		if (wsh_tokenizer(foreach, pipe[counter], 2) == ERROR)
			return (NULL);
		wsh_token->wsh_command = ft_strdup(foreach[i++]);
		if (ft_isbuiltin(wsh_token->wsh_command))
			wsh_token->type = BUILTIN;
		wsh_fillargs(wsh_token, foreach, &i);
		wsh_fillparams(wsh_token, foreach, &i);
		if (pipe[++counter][0] != '\0')
		{
			if (!(wsh_token->next = wsh_token_init()))
				return (NULL);
			wsh_token = wsh_token->next;
		}
	}
	return (wsh_token);
}

t_wsh_tokens	*wsh_parse(char *cmd)
{
	char			array[50][50];
	char			pipe[50][50];
	t_wsh_tokens	*wsh_token;
	t_wsh_tokens	*wsh_token_first;
	int				i;
	int				j;

	i = 0;
	j = 0;
	wsh_token = wsh_token_init();
	if (wsh_tokenizer(array, cmd, 0) == ERROR)
		return (NULL);
	wsh_token_first = wsh_token;
	while (array[i][0] != '\0')
	{
		if (wsh_tokenizer(pipe, array[i], 1) == ERROR)
			return (NULL);
		wsh_token->std_in = 0;
		wsh_token = wsh_fillCommands(wsh_token, pipe);
		if (array[++i][0] != '\0')
		{
			if (!(wsh_token->next = wsh_token_init()))
				return (NULL);
			wsh_token = wsh_token->next;
		}
	}
	return (wsh_token_first);
}
