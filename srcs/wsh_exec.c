/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:46:33 by mashad            #+#    #+#             */
/*   Updated: 2021/03/22 13:16:09 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    *wsh_exec(t_wsh_list *wsh_list)
{
	int i;
	
	i = 0;
	if (wsh_first_char(wsh_list->string))
		ft_putendl_fd("wsh: syntax error near unexpected token `;'", 1);
	while (wsh_list->ast_parsed && wsh_list->ast_parsed->wsh_command)
	{
		if (ft_isbuiltin(wsh_list->ast_parsed->wsh_command) && wsh_list->ast_parsed->std_out == 1 
		&& !wsh_list->ast_parsed->wsh_redi)
			wsh_exec_builtin(wsh_list);
		else if (wsh_list->ast_parsed->type == CMD || wsh_list->ast_parsed->wsh_redi
		|| wsh_list->ast_parsed->std_out != 1)
			wsh_execve(wsh_list);
		wsh_list->ast_parsed = wsh_list->ast_parsed->next;
		i++;
	}
	while(wait(NULL) > 0);
	return (0);
}