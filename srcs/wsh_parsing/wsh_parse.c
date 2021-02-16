/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:25:23 by mashad            #+#    #+#             */
/*   Updated: 2021/01/08 14:51:51 by mashad           ###   ########.fr       */
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
	cmd[i][0] = '\0';
	free(token);
	token = NULL;
    return (1);
}

t_wsh_tokens	*wsh_fillCommands(t_wsh_tokens *wsh_token, char pipe[][50])
{
	char	**tokens;
	int		counter;

	counter = 0;
	if (!(wsh_token->next = (t_wsh_tokens *)malloc(sizeof(t_wsh_tokens))))
		return (NULL);
	while (pipe[counter][0] != '\0')
	{
		
		counter++;
	}
	return (wsh_token);
}

t_wsh_tokens	*wsh_parse( char *cmd )
{
    char			array[50][50];
	char			pipe[50][50];
	t_wsh_tokens	*wsh_token;
	t_wsh_tokens	*wsh_token_first;
    int				i;
	int				j;
    
    i = 0;
	j = 0;
	if (!(wsh_token = (t_wsh_tokens *)malloc(sizeof(t_wsh_tokens))))
		return (NULL);
    if (wsh_tokenizer(array, cmd, 0) == ERROR)
		return (NULL);
	wsh_token_first = wsh_token;
	while (array[i][0] != '\0')
	{
		if (wsh_tokenizer(pipe, array[i], 1) == ERROR)
			return (NULL);
		wsh_token = wsh_fillCommands(wsh_token, pipe);
		wsh_token = wsh_token->next;
		i++;
	}
	return (wsh_token_first);
}