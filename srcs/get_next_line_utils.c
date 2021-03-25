/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:40:46 by sdunckel          #+#    #+#             */
/*   Updated: 2021/03/24 15:45:16 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *s, int gnl)
{
	size_t		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n' && gnl)
			return (i);
		i++;
	}
	return (i);
}

int	ft_char(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char)
			* (ft_strlen_gnl(s1, 0) + ft_strlen_gnl(s2, 0) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	free(s1);
	str[i + j] = EOL;
	return (str);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen_gnl(s, 0))
		return (NULL);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s[start] && len)
	{
		str[i] = s[start];
		i++;
		start++;
		len--;
	}
	str[i] = EOL;
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	i;
	char	*s;

	i = 0;
	mem = (char *)malloc(count * size);
	if (!mem)
		return (NULL);
	s = mem;
	while (i < count * size)
	{
		s[i] = 0;
		i++;
	}
	return (mem);
}
