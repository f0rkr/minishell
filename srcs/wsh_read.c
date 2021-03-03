#include "minishell.h"

char	*wsh_read(int *garbage_flag)
{
	char *string;

	ft_putstr_fd("wsh> ", 1);
	if (get_next_line(0, &string) == ERROR)
	{
		*garbage_flag = ERROR;
		return (NULL);
	}
	return (string);
}