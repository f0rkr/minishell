/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:46:33 by mashad            #+#    #+#             */
/*   Updated: 2021/03/25 17:24:37 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wsh_set_ret(t_wsh_list *wsh_list)
{
	int		c_p;
	char 	*c_var;

	c_var = ft_strdup("?");
	c_p = wsh_searchenvx(wsh_list->wsh_envs, c_var);
	if (c_p)
		wsh_removevarandadd(wsh_list->wsh_envs, ft_strjoin("?=", ft_itoa(wsh_list->ast_parsed->wsh_ret)), c_p);
}

void    *wsh_exec(t_wsh_list *wsh_list)
{
	int		i;
	int		statval;
	t_wsh_tokens *wsh_token;

	i = 0;
	if (wsh_first_char(wsh_list->string))
	{
		ft_putstr_fd("wsh: syntax error near unexpected token `", 1);
		while (wsh_list->string[i] == ';' || wsh_list->string[i] == '|')
		{
				ft_putchar_fd(wsh_list->string[i], 1);
				if (wsh_list->string[i] != wsh_list->string[i + 1])
					break;
				i++;
		}
		ft_putendl_fd("'", 1);
		wsh_list->ast_parsed->wsh_ret = 258;
		wsh_set_ret(wsh_list);
		return (0);
	}
	i = 0;
	if (wsh_list->ast_parsed->wsh_redi)
	{
		if (wsh_list->ast_parsed->wsh_redi->filename[i] == '\0')
		{
			ft_putendl_fd("wsh: syntax error near unexpected token `newline'", 1);
			wsh_list->ast_parsed->wsh_ret = 258;
			wsh_set_ret(wsh_list);
			return (0);
		}
		else if (wsh_list->ast_parsed->wsh_redi->filename[i] == ';' || wsh_list->ast_parsed->wsh_redi->filename[i] == '|' 
		|| wsh_list->ast_parsed->wsh_redi->filename[i] == '>' || wsh_list->ast_parsed->wsh_redi->filename[i] == '<')
		{
			ft_putstr_fd("wsh: syntax error near unexpected token `", 1);
			while (wsh_list->ast_parsed->wsh_redi->filename[i] == ';' || wsh_list->ast_parsed->wsh_redi->filename[i] == '|' 
			|| wsh_list->ast_parsed->wsh_redi->filename[i] == '>' || wsh_list->ast_parsed->wsh_redi->filename[i] == '<')
			{
					ft_putchar_fd(wsh_list->ast_parsed->wsh_redi->filename[i++], 1);
					if (wsh_list->ast_parsed->wsh_redi->filename[i] != wsh_list->ast_parsed->wsh_redi->filename[i + 1])
						break;
			}
			ft_putendl_fd("'", 1);
			wsh_list->ast_parsed->wsh_ret = 258;
			wsh_set_ret(wsh_list);
			return (0);
		}
	}
	i = 0;
	while (wsh_list->ast_parsed && wsh_list->ast_parsed->wsh_command)
	{
		wsh_token = wsh_list->ast_parsed;
		i = 0;
		while (wsh_list->ast_parsed->wsh_param && wsh_list->ast_parsed->wsh_param[i])
		{
			wsh_escape(wsh_list->wsh_envs, wsh_list->ast_parsed->wsh_param[i]);
			i++;
		}
		if (ft_isbuiltin(wsh_list->ast_parsed->wsh_command) && wsh_list->ast_parsed->std_in == 0 
		&& !wsh_list->ast_parsed->wsh_redi)
			wsh_exec_builtin(wsh_list);
		else if (wsh_list->ast_parsed->type == CMD || wsh_list->ast_parsed->wsh_redi
		|| wsh_list->ast_parsed->std_out != 1)
			wsh_execve(wsh_list);
		wsh_list->ast_parsed = wsh_list->ast_parsed->next;
	}
	wsh_list->ast_parsed = wsh_token;
	while(wait(&statval) > 0)
	{
		if(WIFEXITED(statval))
	 		wsh_list->ast_parsed->wsh_ret = WEXITSTATUS(statval);
	}
	wsh_set_ret(wsh_list);
	return (0);
}
