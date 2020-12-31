/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:09:11 by mashad            #+#    #+#             */
/*   Updated: 2019/10/13 15:12:20 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	i;
	int		ps;
	size_t	size;

	size = ft_strlen(s);
	ps = 0;
	i = 0;
	str = (char *)s;
	if (size == 0 && *s != c)
		return (NULL);
	while (i <= size)
	{
		if (str[i] == c)
			ps = i;
		i++;
	}
	if (str[ps] == c)
		return (&str[ps]);
	return (NULL);
}
