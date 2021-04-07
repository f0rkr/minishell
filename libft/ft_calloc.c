/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 23:05:19 by mashad            #+#    #+#             */
/*   Updated: 2021/04/07 13:00:16 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	int		i;

	i = 0;
	mem = malloc(size * count);
	if (mem != NULL)
	{
		while ((int)(count * size) > i)
		{
			*(char *)(mem + i) = 0;
			i++;
		}
		return (mem);
	}
	return (0);
}
