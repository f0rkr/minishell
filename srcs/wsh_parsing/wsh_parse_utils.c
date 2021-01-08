/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:36:56 by mashad            #+#    #+#             */
/*   Updated: 2021/01/08 11:51:39 by mashad           ###   ########.fr       */
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