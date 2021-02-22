/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:36:56 by mashad            #+#    #+#             */
/*   Updated: 2021/02/22 16:48:24 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int		wsh_readSquotes(char *str, const char *string, int *counter)
{
	int i;

	i = 0;
	(*counter)++;
	while (string[*counter] != SQUOTE && string[*counter] != EOL)
		str[i++] = string[(*counter)++];
	str[i] = EOL;
	++(*counter);
	return (1);
}

extern int		wsh_readDquotes(char *str, const char *string, int *counter)
{
	int i;

	i = 0;
	(*counter)++;
	while (string[*counter] != DQUOTE && string[*counter] != EOL)
		str[i++] = string[(*counter)++];
	str[i] = EOL;
	++(*counter);
	return (1);
}

extern int		is_and(const char *str, int p, int q_flag, int pipe)
{
	if (str[p] == AND && str[p-1] != ESC && !q_flag)
		return (1);
	if (str[p] == PIPE && pipe == 1 && str[p-1] != ESC && !q_flag)
		return (1);
	if (str[p] == SPACE && pipe == 2 && str[p-1] != ESC && !q_flag)
		return (1);
	return (0);
}

extern int		wsh_scan_commands(char *str, const char *string, int pipe)
{
	static int 			counter = INIT;
	int					scount;
	int					quote_flag;
	
	scount = INIT;
	quote_flag = 0;
	while (!is_and(string, counter, quote_flag, pipe) && string[counter] != EOL)
	{
		if (ft_isin(string[counter], "\'\"") && string[counter-1] != ESC && quote_flag == 0)
			quote_flag = 1;
		else if (ft_isin(string[counter], "\'\"") && quote_flag == 1)
			quote_flag = 0;
		str[scount++] = string[counter++];
	}
	str[scount] = EOL;
	if (string[counter++] == EOL)
	{
		counter = 0;
		return (0);
	}
	return (1);
}