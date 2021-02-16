#include "minishell.h"

void		wsh_pwd(void)
{
	char	buff[4029];

	getcwd(buff,4029);
	ft_putstr_fd(buff, 0);
	ft_putchar_fd('\n', 0);
	return ;
}