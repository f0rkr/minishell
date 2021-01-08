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

int		is_and(const char *str, int p, int q_flag)
{
	if (str[p] == AND && str[p-1] != ESC && !q_flag)
		return (1);
	return (0);
}

int     wsh_scan_commands(char *str, const char *string)
{
	static int 			counter = INIT;
	int					scount;
	int					quote_flag;
	
	scount = INIT;
	quote_flag = 0;
	while (!is_and(string, counter, quote_flag) && string[counter] != EOL)
	{
		if (ft_isin(string[counter], "\'\"") && string[counter-1] != ESC && quote_flag == 0)
			quote_flag = 1;
		else if (ft_isin(string[counter], "\'\"") && quote_flag == 1)
			quote_flag = 0;
		str[scount++] = string[counter++];
	}
	str[scount] = EOL;
	counter++;
	if (string[counter] == EOL)
	{
		counter = 0;
		return (0);
	}
	return (1);
}

int		wsh_tokenizer(char cmd[][50], char *string)
{
    char    *token;
	int		i;

	i = 0;
	if (!(token = (char *)malloc(sizeof(char) * 50)))
		return (ERROR);
    while (wsh_scan_commands(token, (const char *) string))
    	ft_strlcpy((char *)cmd[i++], (const char *)token, ft_strlen(token)+1);
	ft_strlcpy((char *)cmd[i++], (const char *)token, ft_strlen(token)+1);
	cmd[i][0] = '\0';
	free(token);
	token = NULL;
    return (1);
}

void	*wsh_parse( char *cmd )
{
    char array[50][50];
    int i;
    
    i = 0;
    if (wsh_tokenizer(array, cmd) == ERROR)
		return (NULL);
	
	return (0);
}