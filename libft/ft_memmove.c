/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 20:50:38 by mashad            #+#    #+#             */
/*   Updated: 2019/10/20 16:47:57 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	const unsigned char	*source = src;
	size_t				i;

	if (!dst && !src)
		return (NULL);
	if (ft_memcmp(dst, src, len) == 0)
		return (dst);
	dest = dst;
	if (src <= dst)
	{
		while (len--)
			dest[len] = source[len];
	}
	else
	{
		i = 0;
		while (i++ < len)
			dest[i - 1] = source[i - 1];
	}
	return (dst);
}
