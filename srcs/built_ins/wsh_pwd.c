#include "minishell.h"

void		wsh_pwd(void)
{
	char	buff[4029];

	getcwd(buff,4029);
	ft_putendl_fd(buff, 1);
	exit(0);
}