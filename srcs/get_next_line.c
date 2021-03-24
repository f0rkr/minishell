/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:47:15 by mashad            #+#    #+#             */
/*   Updated: 2021/03/24 15:41:30 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strdel(char **as, char **str, int frenum, int ret)
{
	if (!(as == NULL))
	{
		free(*as);
		*as = NULL;
	}
	if (frenum == 2)
	{
		if (!(str == NULL))
		{
			free(*str);
			*str = NULL;
		}
	}
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char		*s[256];
	char			*buf;
	int				ret;
	char			*tmp;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	if (!s[fd] && !(s[fd] = ft_calloc(1, sizeof(char *))))
		return (-1);
	while ((ft_char('\n', s[fd])) < 0 && (ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		s[fd] = ft_strjoin_gnl(s[fd], buf);
	}
	*line = ft_substr_gnl(s[fd], 0, ft_strlen_gnl(s[fd], 1));
	if ((ft_char('\n', s[fd])) < 0)
		return (ft_strdel(&s[fd], &buf, 2, 0));
	tmp = s[fd];
	s[fd] = ft_substr_gnl(s[fd], ft_char('\n', s[fd]) + 1, ft_strlen_gnl(s[fd], 0));
	return (ft_strdel(&tmp, &buf, 2, 1));
}
