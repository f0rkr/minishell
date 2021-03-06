
include "minishell.h"

void	wsh_getvar(char *command, t_wsh_list *wsh_list)
{

}

void	wsh_fillvar(char *command, t_wsh_list *wsh_list)
{
	int		counter;
	char	*tmp;

	counter = 0;
	if (!(tmp = (char **)malloc(sizeof(char) * 1024)))
		return ;
	if (command[counter] == SQUOTE)
		return ws_readSquotes(command);
	else if (command[counter] == DQUOTE)
		return wsh_readDquotes(command);
	while (command[counter] != '\0')
	{
		
	}
	return ;
}