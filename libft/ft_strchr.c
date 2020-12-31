/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:43:47 by mashad            #+#    #+#             */
/*   Updated: 2019/10/12 13:40:52 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	db;
	char	*str;
	int		size;

	str = (char *)s;
	db = (char)c;
	size = ft_strlen(s);
	while (size >= 0)
	{
		if (*str == db)
			return (str);
		size--;
		str++;
	}
	return (NULL);
}
