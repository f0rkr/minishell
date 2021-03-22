/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:46:33 by mashad            #+#    #+#             */
/*   Updated: 2021/03/22 20:08:56 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    *wsh_exec(t_wsh_list *wsh_list)
{
	int i;
	
	i = 0;
	if (wsh_first_char(wsh_list->string))
	{
		ft_putstr_fd("wsh: syntax error near unexpected token `", 1);
		while (wsh_list->string[i] == ';' || wsh_list->string[i] == '|')
		{
				ft_putchar_fd(wsh_list->string[i], 1);
				if (wsh_list->string[i] != wsh_list->string[i + 1])
					break;
				i++;
		}
		ft_putendl_fd("'", 1);
		return (0);
	}
	i = 0;
	if (wsh_list->ast_parsed->wsh_redi)
	{
		if (wsh_list->ast_parsed->wsh_redi->filename[i] == '\0')
			ft_putendl_fd("wsh: syntax error near unexpected token `newline'", 1);
		else if (wsh_list->ast_parsed->wsh_redi->filename[i] == ';' || wsh_list->ast_parsed->wsh_redi->filename[i] == '|')
		{
			ft_putstr_fd("wsh: syntax error near unexpected token `", 1);
			while (wsh_list->ast_parsed->wsh_redi->filename[i] == ';' || wsh_list->ast_parsed->wsh_redi->filename[i] == '|')
			{
					ft_putchar_fd(wsh_list->ast_parsed->wsh_redi->filename[i++], 1);
					if (wsh_list->ast_parsed->wsh_redi->filename[i] != wsh_list->ast_parsed->wsh_redi->filename[i + 1])
						break;
			}
			ft_putendl_fd("'", 1);
			
		}
		return (0);
	}
	while (wsh_list->ast_parsed && wsh_list->ast_parsed->wsh_command)
	{
		if (ft_isbuiltin(wsh_list->ast_parsed->wsh_command) && wsh_list->ast_parsed->std_out == 1 
		&& !wsh_list->ast_parsed->wsh_redi)
			wsh_exec_builtin(wsh_list);
		else if (wsh_list->ast_parsed->type == CMD || wsh_list->ast_parsed->wsh_redi
		|| wsh_list->ast_parsed->std_out != 1)
			wsh_execve(wsh_list);
		wsh_list->ast_parsed = wsh_list->ast_parsed->next;
	}
	while(wait(NULL) > 0);
	return (0);
}