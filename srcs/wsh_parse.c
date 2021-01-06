/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:25:23 by mashad            #+#    #+#             */
/*   Updated: 2021/01/06 10:45:13 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     wsh_scan_token(char *str, const char *string)
{
	static int 	counter = 0;
	int			scount;
	
	scount = 0;
    while (string[counter] != ' ')
	{
		str[scount++] = string[counter];
		if (string[counter] == '\0' || string[counter] == ';' || string[counter] == '|')
			break;
		counter++;
	}
	str[scount] = '\0';
	if (string[counter] == ' ' || string[counter] == ';' || string[counter] == '|')
		counter++;
	if (string[counter] == '\0')
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
    while (wsh_scan_token(token, (const char *) string))
    	ft_strlcpy((char *)cmd[i++], (const char *)token, ft_strlen(token)+1);
	ft_strlcpy((char *)cmd[i++], (const char *)token, ft_strlen(token)+1);
	cmd[i][0] = 0;
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
	while (array[i][0] != 0)
    {
        printf("%s\n", array[i]);
        i++;
    }
	return (0);
}