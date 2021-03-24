#include "minishell.h"

char	*wsh_read(int *garbage_flag)
{
	char	*string;
	char	buff[4029];

	getcwd(buff, 4029);
	ft_putstr_fd("\x1B[36mwsh\x1B[0m\x1B[34m :: \x1B[0m", 1);
	ft_putstr_fd("\x1B[32m", 1);
	ft_putstr_fd(buff, 1);
	ft_putstr_fd("\x1B[0m\x1B[31m » \x1B[0m", 1);
	if (get_next_line(0, &string) == ERROR)
	{
		*garbage_flag = ERROR;
		return (NULL);
	}
	return (string);
}
