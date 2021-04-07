#include "minishell.h"

void	wsh_pipe(t_wsh_list *wsh_list, char **path)
{
	int	pip[2];

	if (wsh_list->ast_parsed->std_out == 666)
	{
		pipe(pip);
		wsh_list->ast_parsed->std_out = pip[1];
		wsh_list->ast_parsed->next->std_in = pip[0];
	}
	if (wsh_list->ast_parsed->wsh_command[0] == '.')
		*path = ft_strdup(wsh_list->ast_parsed->wsh_command);
}

void	wsh_redi_out(t_wsh_list *wsh_list)
{
	if (wsh_list->ast_parsed->wsh_command[0] == '>')
	{
		if (wsh_list->ast_parsed->wsh_param
			&& wsh_list->ast_parsed->wsh_param[0] != NULL)
			open(wsh_list->ast_parsed->wsh_param[0],
				O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (wsh_list->ast_parsed->wsh_param
			&& wsh_list->ast_parsed->wsh_param[1] != NULL)
		{
			ft_putstr_fd("wsh: ", 1);
			ft_putstr_fd(wsh_list->ast_parsed->wsh_param[1], 1);
			ft_putendl_fd(": command not found", 1);
		}
		if (!wsh_list->ast_parsed->wsh_param)
		{
			ft_putstr_fd("wsh: syntax error near unexpected", 1);
			ft_putendl_fd(" token `newline'", 1);
		}
	}
}

void	wsh_redi_in(t_wsh_list *wsh_list)
{
	if (wsh_list->ast_parsed->wsh_command[0] == '<')
	{
		if (wsh_list->ast_parsed->wsh_param
			&& wsh_list->ast_parsed->wsh_param[0] != NULL)
		{
			ft_putstr_fd("wsh: ", 1);
			ft_putstr_fd(wsh_list->ast_parsed->wsh_param[0], 1);
			ft_putendl_fd(": No such file or directory", 1);
		}
		else
		{
			ft_putstr_fd("wsh: syntax error near unexpected", 1);
			ft_putendl_fd(" token `newline'", 1);
		}
	}
}

void	wsh_exec_parent(t_wsh_list *wsh_list)
{
	if (wsh_list->ast_parsed->std_out != 1)
		close(wsh_list->ast_parsed->std_out);
	if (wsh_list->ast_parsed->std_in != 0)
		close(wsh_list->ast_parsed->std_in);
}
