/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:01:28 by mashad            #+#    #+#             */
/*   Updated: 2019/10/19 10:10:10 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	db;
	size_t			i;

	i = 0;
	db = (unsigned char)c;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == db)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
