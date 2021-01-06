/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:25:23 by mashad            #+#    #+#             */
/*   Updated: 2021/01/06 16:57:29 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		wsh_readQuotes(char *str, const char *string, int *counter)
{
	int i;

	i = 0;
	(*counter)++;
	while (!ft_isin(string[*counter], "\'\"") && string[*counter] != '\0')
		str[i++] = string[(*counter)++];
	str[i] = '\0';
	++(*counter);
	return (1);
}

int     wsh_scan_token(char *str, const char *string)
{
	static int 			counter = INIT;
	int					scount;

	scount = INIT;
	while (!ft_isin(string[counter], " ;|") && string[counter] != '\0')
	{
		if (ft_isin(string[counter], "\'\""))
			return (wsh_readQuotes(str, string, &counter));
		str[scount++] = string[counter++];
	}
	if (ft_isalnum(str[scount-1]))
		str[scount] = '\0';
	else
	{
		str[scount++] = string[counter++];
		str[scount] = '\0';	
	}
	if (string[counter] == '\0')
	{
		counter = INIT;
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
    while (wsh_scan_token(token, (const char *) string))
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
	while (array[i][0] != '\0')
    {
        printf("%s\n", array[i]);
        i++;
    }
	return (0);
}