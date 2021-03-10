/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:49:50 by mashad            #+#    #+#             */
/*   Updated: 2021/03/09 10:54:17 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** WESH SHELL MAIN LOOP
*/

int				wsh_loop(t_wsh_list *wsh_list)
{
	t_wsh_tokens	*wsh_tmp;

	while (1)
	{
		wsh_list->garbage_flag = LOOP;
		wsh_list->string = wsh_read(&wsh_list->garbage_flag);
		if (wsh_list->garbage_flag != ERROR)
			wsh_list->ast_parsed = wsh_parse(wsh_list->string);
		wsh_tmp = wsh_list->ast_parsed;
		if (wsh_list->garbage_flag != ERROR)
			wsh_exec(wsh_list);
		wsh_list->ast_parsed = wsh_tmp;
		if (wsh_garbageCollector(wsh_list) == ERROR)
			return (ERROR);
	}
	wsh_list->garbage_flag = ENDEXEC;
	return (EXIT);
}

/*
** WESH SHELL STRUCT INIT
*/
t_wsh_tokens	*wsh_token_init()
{
	t_wsh_tokens	*wsh_token;

	if (!(wsh_token = (t_wsh_tokens *)malloc(sizeof(t_wsh_tokens))))
		return (NULL);
	wsh_token->type = CMD;
	wsh_token->wsh_command = NULL;
	wsh_token->wsh_arg = NULL;
	wsh_token->wsh_param = NULL;
	wsh_token->std_in = STDIN;
	wsh_token->std_out = STDOUT;
	wsh_token->next = NULL;
	return (wsh_token);
}

t_wsh_list		*wsh_init(char *env[])
{
	t_wsh_list	*wsh_list;
	int			i;

	i = 0;
	wsh_list = (t_wsh_list *)malloc(sizeof(t_wsh_list) * 1);
	wsh_list->string = NULL;
	wsh_list->garbage_flag = INIT;
	wsh_list->ast_parsed = NULL;
	wsh_list->wsh_envs = (char **)malloc(sizeof(char) * 4029);
	while (env[i])
	{
		wsh_list->wsh_envs[i] = ft_strdup(env[i]);
		i++;
	}
	return (wsh_list);
}

int				main(int argc, char **argv, char **env)
{
	t_wsh_list *wsh_list;

	(void)argv;
	if (!(wsh_list = wsh_init(env)))
	{
		wsh_garbageCollector(wsh_list);
		return (ERROR);
	}
	if (argc != 1)
		return (ERROR);
	if (wsh_loop(wsh_list) == ERROR)
		return (ERROR);
	wsh_garbageCollector(wsh_list);
	return (EXIT);
}