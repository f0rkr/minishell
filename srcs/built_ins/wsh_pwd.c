#include "minishell.h"

void		wsh_pwd(t_wsh_tokens *wsh_token)
{
	char	buff[4029];

	getcwd(buff,4029);
	ft_putendl_fd(buff, 1);
	if (wsh_token->std_out == 1)
		return ;
	else
		exit(0);
}