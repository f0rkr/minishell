/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_garbageCollector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:50:06 by mashad            #+#    #+#             */
/*   Updated: 2021/01/05 15:50:08 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wsh_free(void **data)
{
	if (data)
	{
		free(*data);
		*data = NULL;
	}
	return ;
}

void	wsh_loop_free(void **data)
{
	int counter;

	counter = 0;
	if (data)
	{
		while (data[counter])
			wsh_free((void **) &data[counter++]);
		free(data);
		data = NULL;
	}
	return ;
}
int     wsh_garbageCollector(t_wsh_list *wsh_list)
{
	int				counter;
	t_wsh_tokens	*wsh_tmp;

	counter = 0;
	wsh_free((void **) &wsh_list->string);
	while (wsh_list->ast_parsed)
	{
		if (wsh_list->ast_parsed->wsh_command)
			wsh_free((void **) &wsh_list->ast_parsed->wsh_command);
		wsh_loop_free((void **)wsh_list->ast_parsed->wsh_arg);
		wsh_loop_free((void **)wsh_list->ast_parsed->wsh_param);
		wsh_tmp = wsh_list->ast_parsed;
		wsh_list->ast_parsed = wsh_list->ast_parsed->next;
		wsh_free((void **) &wsh_tmp);
	}
    if (wsh_list->garbage_flag != LOOP)
		wsh_loop_free((void **)wsh_list->wsh_envs);
	wsh_free((void **) &wsh_list->ast_parsed);
	if (wsh_list->garbage_flag == ERROR)
    {
        wsh_list->garbage_flag = INIT;
        return (ERROR);
    }
    return (EXIT);
}