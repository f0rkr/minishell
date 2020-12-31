/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:13:55 by mashad            #+#    #+#             */
/*   Updated: 2019/10/09 22:28:39 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned char	db;
	size_t			i;

	str = (unsigned char *)b;
	db = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		str[i] = db;
		i++;
	}
	return (b);
}
