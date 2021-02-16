/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:46:33 by mashad            #+#    #+#             */
/*   Updated: 2021/01/05 16:13:49 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    *wsh_exec( t_wsh_list *wsh_list )
{
	printf("%d\n", wsh_list->ast_parsed->next->type);
	// while ( wsh_list->ast_parsed )
	// {
	// 	if (wsh_list->ast_parsed->type == BUILTIN)
	// 		wsh_builtins(wsh_list->ast_parsed, wsh_list);
	// 	// working to another time
	// 	wsh_list->ast_parsed = wsh_list->ast_parsed->next;
	// }
	return (0);
}