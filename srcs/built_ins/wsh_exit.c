#include "minishell.h"

void	wsh_exit(t_wsh_list *wsh_list)
{
	if (wsh_list->ast_parsed->std_out == 1)
	{
		wsh_list->garbage_flag = ENDEXEC;
		wsh_garbageCollector(wsh_list);
		exit(0);
	}
	return ;
}