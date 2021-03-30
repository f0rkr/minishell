/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:34:10 by mashad            #+#    #+#             */
/*   Updated: 2019/10/10 13:22:40 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		v;
	size_t		len;

	len = ft_strlen(src);
	i = 0;
	while (*dst != EOL && i < size)
	{
		dst++;
		i++;
	}
	v = size - i;
	if (v == 0)
		return (i + ft_strlen(src));
	while (*src != EOL && v != 1)
	{
		*dst++ = *src;
		v--;
		src++;
	}
	*dst = EOL;
	return (i + len);
}
