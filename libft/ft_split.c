/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:54:06 by mashad            #+#    #+#             */
/*   Updated: 2021/04/07 12:59:56 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	tab_aloc(char *str, char m)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] != EOL)
	{
		if (str[i] == m)
			i++;
		else
		{
			c++;
			while (str[i] != EOL)
			{
				if (str[i] == m)
					break ;
				i++;
			}
		}
	}
	return (c);
}

static int	string(char *str, int *k, char m)
{
	int	c;

	c = 0;
	while (str[*k] != EOL)
	{
		if (str[*k] == m)
			*k += 1;
		else
		{
			while (str[*k] != EOL && str[*k] != m)
			{
				c++;
				*k += 1;
			}
			*k += 1;
			return (c);
		}
	}
	return (0);
}

static char	**ft_append(char **tab, char *str, int i, char m)
{
	int	j;
	int	r;

	j = 0;
	while (str[i] != EOL)
	{
		r = 0;
		while (str[i] == m)
			i++;
		if (str[i] == EOL)
			break ;
		while (str[i] != m && str[i] != EOL)
		{
			tab[j][r] = str[i];
			i++;
			r++;
			if (str[i] == EOL)
				break ;
		}
		tab[j][r] = EOL;
		j++;
	}
	tab[j] = 0;
	return (tab);
}

static void	ft_fre(char **tab, int r)
{
	while (r)
	{
		free(tab[r]);
		r--;
	}
	free(tab);
}

char	**ft_split(char const *str, char c)
{
	char	**tab;
	int		i;
	int		*k;
	int		p;
	int		r;

	r = 0;
	i = 0;
	p = 0;
	k = &p;
	if (!str)
		return (0);
	tab = (char **)malloc(sizeof(char *)*(tab_aloc((char *)str, c) + 1));
	while (r < tab_aloc((char *)str, c))
	{
		tab[r] = malloc(sizeof(char) * (string((char *)str, k, c) + 1));
		if (!tab[r])
		{
			ft_fre(tab, r);
			return (0);
		}
		r++;
	}
	ft_append(tab, (char *)str, i, c);
	return (tab);
}
