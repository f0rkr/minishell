/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:49:42 by mashad            #+#    #+#             */
/*   Updated: 2019/10/19 10:00:42 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s1;
	char	*s2;
	int		i;

	if (!dst && !src)
		return (0);
	i = 0;
	s1 = (char *)dst;
	s2 = (char *)src;
	while (i < (int)n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dst);
}
