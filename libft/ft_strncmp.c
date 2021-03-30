/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:03:24 by mashad            #+#    #+#             */
/*   Updated: 2019/10/19 13:15:08 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (*s1 == *s2 && *s1 != EOL && i < n)
	{
		s1++;
		s2++;
		i++;
	}
	if (i != n)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}
