/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:46:33 by mashad            #+#    #+#             */
/*   Updated: 2021/02/26 16:28:59 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    *wsh_exec(t_wsh_list *wsh_list)
{
	t_wsh_tokens	*wsh_tmp;

	wsh_tmp = wsh_list->ast_parsed
	while (wsh_tmp->next)
	{
		if (wsh_tmp->type == BUILTIN)
			wsh_exec_builtin(wsh_list);
		wsh_tmp = wsh_tmp->next;
	}
	return (0);
}