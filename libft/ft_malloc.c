#include "libft.h"

void		*g_alloc[400];
int			g_ab = 0;

void				ft_free(void)
{
	int i;
	i = -1;
	while (++i < g_ab)
		free(g_alloc[i]);
}

void				*ft_malloc(size_t n)
{
	void	*tmp;
	if (!(tmp = malloc(n)))
		return (NULL);
	g_alloc[g_ab] = tmp;
	g_ab++;
	return (tmp);
}