/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:11:25 by mashad            #+#    #+#             */
/*   Updated: 2019/10/19 10:12:44 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*src;
	unsigned char	*dst;
	size_t			i;

	i = 0;
	if (n == 0)
		return (0);
	src = (unsigned char *)s1;
	dst = (unsigned char *)s2;
	while (i < n)
	{
		if (src[i] != dst[i])
			return (src[i] - dst[i]);
		i++;
	}
	return (0);
}
