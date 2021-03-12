/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:46:33 by mashad            #+#    #+#             */
/*   Updated: 2021/03/12 15:43:19 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    *wsh_exec(t_wsh_list *wsh_list)
{
	while (wsh_list->ast_parsed)
	{
		if (!ft_strncmp(wsh_list->ast_parsed->wsh_command, "exit", 5))
			wsh_exit(wsh_list);
		if (!ft_strncmp(wsh_list->ast_parsed->wsh_command, "cd", 3))
			wsh_cd(wsh_list);
		if (!ft_strncmp(wsh_list->ast_parsed->wsh_command, "unset", 6))
			wsh_unset(wsh_list->ast_parsed, wsh_list);
		else
			wsh_execve(wsh_list);
		wsh_list->ast_parsed = wsh_list->ast_parsed->next;
	}
	return (0);
}