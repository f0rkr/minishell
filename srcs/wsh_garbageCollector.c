/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_garbageCollector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:50:06 by mashad            #+#    #+#             */
/*   Updated: 2021/03/26 18:38:54 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wsh_free(char **data)
{
	if (*data && *data[0] != '\0')
	{
		free(*data);
		*data = NULL;
	}
	return ;
}

void	wsh_loop_free(char **data)
{
	int	counter;

	counter = 0;
	if (data != NULL)
	{
		while (data[counter] && data[counter][0] != '\0')
		{
			free(data[counter++]);
			data[counter - 1] = NULL;
		}
		free(data);
		data = NULL;
	}
	return ;
}

void	wsh_garbage_redi(t_wsh_list *wsh_list)
{
	t_wsh_redi		*wsh_tmp_redi;

	while (wsh_list->ast_parsed->wsh_redi)
	{
		wsh_free(&wsh_list->ast_parsed->wsh_redi->filename);
		wsh_free(&wsh_list->ast_parsed->wsh_redi->type);
		wsh_tmp_redi = wsh_list->ast_parsed->wsh_redi;
		wsh_list->ast_parsed->wsh_redi = wsh_list->ast_parsed->wsh_redi->next;
		free(wsh_tmp_redi);
		wsh_tmp_redi = NULL;
	}
}

int	wsh_garbageCollector(t_wsh_list *wsh_list)
{
	t_wsh_tokens	*wsh_tmp;

	free(wsh_list->string);
	wsh_list->string = NULL;
	while (wsh_list->ast_parsed)
	{
		wsh_garbage_redi(wsh_list);
		free(wsh_list->ast_parsed->wsh_command);
		wsh_loop_free(wsh_list->ast_parsed->wsh_arg);
		wsh_loop_free(wsh_list->ast_parsed->wsh_param);
		wsh_tmp = wsh_list->ast_parsed;
		wsh_list->ast_parsed = wsh_list->ast_parsed->next;
		free(wsh_tmp);
		wsh_tmp = NULL;
	}
	if (wsh_list->garbage_flag != LOOP)
		wsh_loop_free(wsh_list->wsh_envs);
	if (wsh_list->garbage_flag == ERROR)
	{
		wsh_list->garbage_flag = INIT;
		return (ERROR);
	}
	if (wsh_list->garbage_flag == ENDEXEC)
		wsh_loop_free(wsh_list->wsh_history);
	return (EXIT);
}
