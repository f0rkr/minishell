/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:46:33 by mashad            #+#    #+#             */
/*   Updated: 2021/03/10 18:37:53 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    *wsh_exec(t_wsh_list *wsh_list)
{
	int i; 

	i = 0;
	while (wsh_list->ast_parsed)
	{
		if (wsh_list->ast_parsed->type == BUILTIN)
			wsh_exec_builtin(wsh_list);
		else
			wsh_execve(wsh_list);
		
		wsh_list->ast_parsed = wsh_list->ast_parsed->next;
		i++;
	}
	return (0);
}