/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:46:33 by mashad            #+#    #+#             */
/*   Updated: 2021/04/07 13:05:24 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wsh_token_error(t_wsh_list *wsh_list)
{
	int	i;

	i = 0;
	if (wsh_first_char(wsh_list->string))
	{
		ft_putstr_fd("wsh: syntax error near unexpected token `", 1);
		while (wsh_list->string[i] == ';' || wsh_list->string[i] == '|')
		{
			ft_putchar_fd(wsh_list->string[i], 1);
			if (wsh_list->string[i] != wsh_list->string[i + 1])
				break ;
			i++;
		}
		ft_putendl_fd("'", 1);
		g_tab[0] = 258;
		return (0);
	}
	return (1);
}

int	wsh_redi_error(t_wsh_redi *wsh_redi, int i)
{
	if (wsh_redi->filename[i] == EOL)
	{
		ft_putendl_fd("wsh: syntax error near unexpected token `newline'", 1);
		g_tab[0] = 258;
		return (0);
	}
	else if (wsh_redi->filename[i] == ';' || wsh_redi->filename[i] == '|'
		|| wsh_redi->filename[i] == '>' || wsh_redi->filename[i] == '<')
	{
		ft_putstr_fd("wsh: syntax error near unexpected token `", 1);
		while (wsh_redi->filename[i] == ';' || wsh_redi->filename[i] == '|'
			|| wsh_redi->filename[i] == '>' || wsh_redi->filename[i] == '<')
		{
			ft_putchar_fd(wsh_redi->filename[i++], 1);
			if (wsh_redi->filename[i - 1] != wsh_redi->filename[i])
				break ;
		}
		ft_putendl_fd("'", 1);
		g_tab[0] = 258;
		return (0);
	}
	return (1);
}

void	wsh_exec_loop_norm(t_wsh_list *list, int statval)
{
	if (ft_isbuiltin(list->ast_parsed->wsh_command)
		&& list->ast_parsed->std_out == 1 && !list->ast_parsed->wsh_redi)
		wsh_exec_builtin(list);
	else if (list->ast_parsed->type == CMD || list->ast_parsed->wsh_redi
		|| list->ast_parsed->std_out != 1)
		wsh_execve(list);
	if (list->ast_parsed->std_out == 1)
		while (wait(&statval) > 0)
			if (WIFEXITED(statval))
				g_tab[0] = WEXITSTATUS(statval);
}

void	wsh_exec_loop(t_wsh_list *list, int statval, int i)
{
	char	*tmp;

	while (list->ast_parsed && list->ast_parsed->wsh_command)
	{
		i = 0;
		if (list->ast_parsed->wsh_command[0] == EOL)
			break ;
		while (list->ast_parsed->wsh_param && list->ast_parsed->wsh_param[i])
		{
			tmp = list->ast_parsed->wsh_param[i];
			list->ast_parsed->wsh_param[i] = wsh_escape(
					list, list->ast_parsed->wsh_param[i]);
			wsh_free(&tmp);
			i++;
		}
		wsh_exec_loop_norm(list, statval);
		g_tab[1] = 0;
		if (list->ast_parsed->next)
			list->ast_parsed = list->ast_parsed->next;
		else
			break ;
	}
}

void	wsh_exec(t_wsh_list *wsh_list)
{
	int				i;
	int				statval;

	i = 0;
	statval = 0;
	if (!wsh_token_error(wsh_list))
		return ;
	if (wsh_list->ast_parsed->wsh_redi
		&& !wsh_redi_error(wsh_list->ast_parsed->wsh_redi, i))
		return ;
	wsh_exec_loop(wsh_list, statval, i);
	while (wait(&statval) > 0)
		if (WIFEXITED(statval))
			g_tab[0] = WEXITSTATUS(statval);
	return ;
}
