#include "libft.h"

extern void			*g_alloc[400];
extern int			g_al = 0;

void				ft_free(void)
{
	int i;
	i = -1;
	while (++i < g_al)
		free(g_alloc[i]);
}

void				*ft_malloc(size_t n)
{
	void	*tmp;
	if (!(tmp = malloc(n)))
		return (NULL);
	g_alloc[g_al] = tmp;
	g_al++;
	return (tmp);
}