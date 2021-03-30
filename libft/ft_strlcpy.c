/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:46:29 by mashad            #+#    #+#             */
/*   Updated: 2019/10/12 19:35:40 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (dst == NULL || src == NULL)
		return (0);
	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (ft_strlen(src) == 0)
	{
		*dst = EOL;
		return (0);
	}
	while (src[i] != EOL && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = EOL;
	return (ft_strlen(src));
}
