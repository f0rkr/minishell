#ifndef LIBFT_H
# define LIBFT_H

/* Library Needed */
# include <unistd.h>
# include <stdlib.h>

/* Functions prototype */
void		ft_putchar_fd(int fd, const char c);
void		ft_putstr_fd(int fd, const char *str);
int			ft_strlen(const char *str);
char		*ft_strcmp(const char *src, const char *dst);
char		*ft_strcpy(const char *src, char *dst);

#endif