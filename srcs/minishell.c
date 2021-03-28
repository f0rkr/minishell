/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:49:50 by mashad            #+#    #+#             */
/*   Updated: 2021/03/28 17:06:52 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** WESH SHELL MAIN LOOP
*/

void	handle_sigin(int sig)
{
	char	buff[4029];
	
	(void)sig;
	if (g_pid == 0)
	{
		getcwd(buff, 4029);
		ft_putstr_fd("\n\x1B[36mwsh\x1B[0m\x1B[34m :: \x1B[0m", 0);
		ft_putstr_fd("\x1B[32m", 0);
		ft_putstr_fd(buff, 0);
		ft_putstr_fd("\x1B[0m\x1B[31m » \x1B[0m", 0);
		// if (g_string)
		// {
		// 	wsh_free((void*)g_string);
		// 	g_string = NULL;
		// }
	}
	else if (g_pid != 0)
	{
		write(1, "\n", 1);
		g_status = 130;
		// if (g_string)
		// {
		// 	wsh_free((void*)g_string);
		// 	g_string = NULL;
		// }
	}
	return ;
}

void	handle_quit(int sig)
{
	(void)sig;
	if (g_pid != 0)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_status = 131;
	}
	return ;
}

int	wsh_loop(t_wsh_list *wsh_list)
{
	t_wsh_tokens	*wsh_tmp;
	char			*line_tmp;

	line_tmp = ft_strdup("");
	while (1)
	{
		wsh_list->garbage_flag = LOOP;
		g_string = wsh_read(wsh_list, &wsh_list->garbage_flag, &line_tmp);
		wsh_list->string = g_string;
		if (wsh_list->garbage_flag != ERROR)
			wsh_list->ast_parsed = wsh_parse(wsh_list->wsh_envs, wsh_list->string);
		wsh_tmp = wsh_list->ast_parsed;
		if (wsh_list->garbage_flag != ERROR)
			wsh_exec(wsh_list);
		wsh_list->ast_parsed = wsh_tmp;
		if (wsh_garbageCollector(wsh_list) == ERROR)
			return (ERROR);
	}
	wsh_free((void *)line_tmp);
	wsh_list->garbage_flag = ENDEXEC;
	return (EXIT);
}

/*
** WESH SHELL STRUCT INIT
*/

t_wsh_redi	*wsh_redi_init(void)
{
	t_wsh_redi	*wsh_redi;

	wsh_redi = (t_wsh_redi *)malloc(sizeof(t_wsh_redi));
	if (!wsh_redi)
		return (NULL);
	wsh_redi->filename = NULL;
	wsh_redi->type = NULL;
	wsh_redi->next = NULL;
	return (wsh_redi);
}

t_wsh_tokens	*wsh_token_init(void)
{
	t_wsh_tokens	*wsh_token;

	wsh_token = (t_wsh_tokens *)malloc(sizeof(t_wsh_tokens));
	if (!(wsh_token))
		return (NULL);
	wsh_token->type = CMD;
	wsh_token->wsh_command = NULL;
	wsh_token->wsh_arg = NULL;
	wsh_token->wsh_param = NULL;
	wsh_token->std_in = STDIN;
	wsh_token->std_out = STDOUT;
	wsh_token->next = NULL;
	wsh_token->wsh_redi = NULL;
	g_status = 0;
	return (wsh_token);
}



t_wsh_list	*wsh_init(char *env[])
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
	wsh_list->wsh_envs[i++] = ft_strdup("?=0");
	wsh_list->wsh_envs[i] = NULL;
	return (wsh_list);
}

int	main(int argc, char **argv, char **env)
{
	t_wsh_list	*wsh_list;

	(void)argv;
	g_pid = 0;
	signal(SIGINT, handle_sigin);
	signal(SIGQUIT, handle_quit);
	wsh_list = wsh_init(env);
	if (!wsh_list)
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
