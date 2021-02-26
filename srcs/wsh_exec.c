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

void    *wsh_exec( t_wsh_list *wsh_list )
{
	while (wsh_list->ast_parsed->next)
	{
		if (wsh_list->ast_parsed->type == BUILTIN)
			wsh_exec_builtin(wsh_list);
		wsh_list->ast_parsed = wsh_list->ast_parsed->next;
	}
	return (0);
}

	//printf("%s\n", wsh_list->ast_parsed->next->wsh_command);
	// while (wsh_list->ast_parsed->next)
	// {
	// 	i = 0;
	// 	printf("command:\t%s\t:params:\t\t:\targs:\t\t:\tin\t%d\t:\tout\t%d\t\n", wsh_list->ast_parsed->wsh_command, wsh_list->ast_parsed->std_in, wsh_list->ast_parsed->std_out);	
	// 	if (wsh_list->ast_parsed->wsh_param[i][0] != '\0')
	// 	{
	// 		while (wsh_list->ast_parsed->wsh_param[i][0] != '\0')
	// 		{
	// 			printf("command:\t\t:params:\t%s\t:\targs:\t\t:\tin\t\t:\tout\t\t\n", wsh_list->ast_parsed->wsh_param[i]);
	// 			i++;
	// 		}
	// 	}
	// 	i = 0;
	// 	if (wsh_list->ast_parsed->wsh_arg[i][0] != '\0')
	// 	{
	// 		while (wsh_list->ast_parsed->wsh_arg[i][0] != '\0')
	// 		{
	// 			printf("command:\t\t:params:\t\t:\targs:\t%s\t:\tin\t\t:\tout\t\t\n", wsh_list->ast_parsed->wsh_arg[i]);
	// 			i++;
	// 		}
	// 	}
	// 	if (wsh_list->ast_parsed->std_in != 0 && wsh_list->ast_parsed->std_in != 1)
	// 		close(wsh_list->ast_parsed->std_in);
	// 	if (wsh_list->ast_parsed->std_out != 0 && wsh_list->ast_parsed->std_out != 1)
	// 		close(wsh_list->ast_parsed->std_out);
	// 	wsh_list->ast_parsed = wsh_list->ast_parsed->next;
	// }