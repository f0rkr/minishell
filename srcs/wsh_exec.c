/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:46:33 by mashad            #+#    #+#             */
/*   Updated: 2021/03/06 17:48:21 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    *wsh_exec(t_wsh_list *wsh_list)
{
	while (wsh_list->ast_parsed)
	{
		if (wsh_list->ast_parsed->type == BUILTIN)
			wsh_exec_builtin(wsh_list);
		// else
		// 	wsh_exec_cmd(wsh_list);
		wsh_list->ast_parsed = wsh_list->ast_parsed->next;
	}
	return (0);
}