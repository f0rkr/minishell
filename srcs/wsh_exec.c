/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:46:33 by mashad            #+#    #+#             */
/*   Updated: 2021/03/29 12:21:11 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wsh_token_error(t_wsh_list *wsh_list)
{
	int	i;

	i = 0;
	if (wsh_first_char(wsh_list->string))
	{
		ft_putstr_fd("wsh: syntax error near unexpected token `", 1);
		while (wsh_list->string[i] == ';' || wsh_list->string[i] == '|')
		{
			ft_putchar_fd(wsh_list->string[i], 1);
			if (wsh_list->string[i] != wsh_list->string[i + 1])
				break ;
			i++;
		}
		ft_putendl_fd("'", 1);
		g_status = 258;
		return (0);
	}
	return (1);
}

int	wsh_redi_error(t_wsh_redi *wsh_redi, int i)
{
	if (wsh_redi->filename[i] == EOL)
	{
		ft_putendl_fd("wsh: syntax error near unexpected token `newline'", 1);
		g_status = 258;
		return (0);
	}
	else if (wsh_redi->filename[i] == ';' || wsh_redi->filename[i] == '|'
		|| wsh_redi->filename[i] == '>' || wsh_redi->filename[i] == '<')
	{
		ft_putstr_fd("wsh: syntax error near unexpected token `", 1);
		while (wsh_redi->filename[i] == ';' || wsh_redi->filename[i] == '|'
			|| wsh_redi->filename[i] == '>' || wsh_redi->filename[i] == '<')
		{
			ft_putchar_fd(wsh_redi->filename[i++], 1);
			if (wsh_redi->filename[i - 1] != wsh_redi->filename[i])
				break ;
		}
		ft_putendl_fd("'", 1);
		g_status = 258;
		return (0);
	}
	return (1);
}

void	wsh_exec_loop(t_wsh_list *wsh_list, int statval, int i)
{
	while (wsh_list->ast_parsed && wsh_list->ast_parsed->wsh_command)
	{
		i = 0;
		if (wsh_list->ast_parsed->wsh_command[0] == EOL)
			break ;
		while (wsh_list->ast_parsed->wsh_param && wsh_list->ast_parsed->wsh_param[i])
			wsh_escape(wsh_list, wsh_list->ast_parsed->wsh_param[i++]);
		if (ft_isbuiltin(wsh_list->ast_parsed->wsh_command)
			&& wsh_list->ast_parsed->std_out == 1 && !wsh_list->ast_parsed->wsh_redi)
			wsh_exec_builtin(wsh_list);
		else if (wsh_list->ast_parsed->type == CMD || wsh_list->ast_parsed->wsh_redi
			|| wsh_list->ast_parsed->std_out != 1)
			wsh_execve(wsh_list);
		if (wsh_list->ast_parsed->std_out == 1)
			while (wait(&statval) > 0)
				if (WIFEXITED(statval))
					g_status = WEXITSTATUS(statval);
		g_pid = 0;
		if (wsh_list->ast_parsed->next)
			wsh_list->ast_parsed = wsh_list->ast_parsed->next;
		else
			break ;
	}
}

void	wsh_exec(t_wsh_list *wsh_list)
{
	int				i;
	int				statval;

	i = 0;
	statval = 0;
	if (!wsh_token_error(wsh_list))
		return ;
	if (wsh_list->ast_parsed->wsh_redi
		&& !wsh_redi_error(wsh_list->ast_parsed->wsh_redi, i))
		return ;
	wsh_exec_loop(wsh_list, statval, i);
	while (wait(&statval) > 0)
		if (WIFEXITED(statval))
			g_status = WEXITSTATUS(statval);
	return ;
}
