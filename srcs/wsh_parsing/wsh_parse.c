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

int	g_i;
int g_j;

int				ft_ispipe(t_wsh_tokens *wsh_token, char token[][50], int ret)
{
	int pip[2];

	while (token[g_i][0] != '\0')
		g_i++;
	if (g_i == g_j)
		return (ret);
	if (pipe(pip)  == -1)
		return (ret);	
	wsh_token->next->std_in = pip[1];
	g_j++;
	return (pip[0]);
}

t_wsh_tokens	*wsh_fillCommands(t_wsh_tokens *wsh_token, char pipe[][50])
{
	t_wsh_tokens	*token;
	int				counter;
	char 			cmd[50][50];
	int				i;
	int				j;

	counter = 0;
	g_i = 0;
	g_j = 1;
	i = 0;
	token = wsh_token;
	while (pipe[counter][0] != '\0')
	{
		i = 0;
		if (!(wsh_tokenizer(cmd, (char *)pipe[counter], 2)))
			return (NULL);
		if (!(wsh_token->wsh_param = (char **)malloc(sizeof(char *) * 100)) ||
		!(wsh_token->wsh_arg = (char **)malloc(sizeof(char *) * 100)))
			return (NULL);
		wsh_token->wsh_arg[0] = ft_strdup("");
		wsh_token->wsh_param[0] = ft_strdup("");
		if (ft_isbuiltin((const char *)cmd[i]))
			wsh_token->type = BUILTIN;
		else
			wsh_token->type = CMD;
		wsh_token->wsh_command = ft_strdup(cmd[i++]);
		j = 0;
		if (cmd[i])
		{
			while (cmd[i][0] == '-')
			{
				wsh_token->wsh_arg[j++] = ft_strdup(cmd[i]);
				wsh_token->wsh_arg[j] = ft_strdup("");
				i++;
			}
			j = 0;
			while (cmd[i][0] != '\0')
			{
				wsh_token->wsh_param[j++] = ft_strdup(cmd[i]);
				wsh_token->wsh_param[j] = ft_strdup("");
				i++;
			}
		}
		counter++;
		wsh_token->std_out = ft_ispipe(wsh_token, pipe, 1);
		if (pipe[counter][0] != '\0')
			if (!(wsh_token->next = wsh_token_init()))
				return (NULL);
		wsh_token = wsh_token->next;
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
		i++;
	}
	return (wsh_token_first);
}
