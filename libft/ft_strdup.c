/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:48:15 by mashad            #+#    #+#             */
/*   Updated: 2021/02/22 15:57:55 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	size_t	i;
	char	*s;

	i = 0;
	size = ft_strlen(s1) + 1;
	s = (char *)malloc(sizeof(char) * size);
	if (s == NULL)
		return (NULL);
	while (s1[i] != EOL)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = EOL;
	return (s);
}
