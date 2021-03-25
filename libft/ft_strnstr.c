/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:21:36 by mashad            #+#    #+#             */
/*   Updated: 2019/10/10 12:40:25 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	char		*hay;
	char		*need;
	size_t		j;

	hay = (char *)haystack;
	need = (char *)needle;
	i = 0;
	if (*needle == EOL)
		return (hay);
	while (hay[i] != EOL && i < len)
	{
		j = 0;
		if (hay[i] == need[j])
		{
			while (need[j] != EOL && hay[i + j] == need[j] && i + j < len)
				j++;
			if (j == ft_strlen(needle))
				return (&hay[i]);
		}
		i++;
	}
	return (NULL);
}
