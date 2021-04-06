/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:55:41 by mashad            #+#    #+#             */
/*   Updated: 2019/10/22 14:55:43 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_length(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	int_size(int n)
{
	int	i;

	i = 1;
	n /= 10;
	while (n)
	{
		n /= 10;
		i *= 10;
	}
	return (i);
}

static char	*ft_negatif(char *s, int size, int n, int i)
{
	unsigned int	nb;

	nb = -n;
	s[i] = '-';
	i++;
	while (size)
	{
		s[i] = (nb / size) + '0';
		nb %= size;
		size /= 10;
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	int		i;
	int		size;
	char	*s;

	s = (char *)malloc(sizeof(char) * (int_length(n) + 1));
	if (!s)
		return (0);
	i = 0;
	size = int_size(n);
	if (n < 0)
		return (ft_negatif(s, size, n, i));
	else if (n >= 0)
	{
		while (size)
		{
			s[i++] = (n / size) + '0';
			n %= size;
			size /= 10;
		}
		s[i++] = '\0';
	}
	return (s);
}
