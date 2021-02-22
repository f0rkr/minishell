/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:46:33 by mashad            #+#    #+#             */
/*   Updated: 2021/02/22 17:38:34 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    *wsh_exec( t_wsh_list *wsh_list )
{
	int i ;
	//printf("%s\n", wsh_list->ast_parsed->next->wsh_command);
	while (wsh_list->ast_parsed->type == 1)
	{
		i = 1;
		printf("command:\t;%s;\t:params:\t;%s;\t:\targs:\t%s\t:\tin\t';%d;\t:\tout\t;%d;\n", wsh_list->ast_parsed->wsh_command, wsh_list->ast_parsed->wsh_param[0], wsh_list->ast_parsed->wsh_arg[0], wsh_list->ast_parsed->std_in, wsh_list->ast_parsed->std_out);
		if (wsh_list->ast_parsed->wsh_param != '\0')
		{
			while (wsh_list->ast_parsed->wsh_param[i][0] != '\0')
			{
				printf("command:\t\t:params:\t%s\t:\targs:\t\t:\tin\t\t:\tout\t\n", wsh_list->ast_parsed->wsh_param[i]);
				i++;
			}
		}
		i = 1;
		if (wsh_list->ast_parsed->wsh_arg != '\0')
		{
			while (wsh_list->ast_parsed->wsh_arg[i][0] != '\0')
			{
				printf("command:\t\t:params:\t\t:\targs:\t%s\t:\tin\t\t:\tout\t\n", wsh_list->ast_parsed->wsh_arg[i]);
				i++;
			}
		}
		wsh_list->ast_parsed = wsh_list->ast_parsed->next;
	}
	return (0);
}