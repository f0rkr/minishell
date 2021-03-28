/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:39:56 by mashad            #+#    #+#             */
/*   Updated: 2021/03/28 12:13:08 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wsh_cd_error(char **tmp)
{
	ft_putstr_fd("wsh: cd: ", 2);
	ft_putstr_fd(*tmp, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	wsh_free((void *) *tmp);
}

void	wsh_change_pwd(char **envs, char *str)
{
	char	buff[4029];
	char	*tmp;
	int		c_pos;
	int		c_p;

	tmp = NULL;
	getcwd(buff, 4029);
	c_p = wsh_searchenvx(envs, "PWD");
	c_pos = wsh_findeq(envs[c_p]);
	if (str == NULL)
		wsh_removevarandadd(envs, ft_strjoin("PWD=", buff), c_p);
	else
		wsh_removevarandadd(envs, ft_strjoin(envs[c_p], "/."), c_p);
	wsh_free((void *)tmp);
}

void	wsh_cd_dot(t_wsh_list *wsh_list, t_wsh_tokens *wsh_token, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(wsh_token->wsh_param[0], ".", 2) == 0)
	{
		tmp = ft_strjoin(wsh_get_envar("PWD", wsh_list->wsh_envs), "/");
		if (opendir(tmp) == NULL)
		{
			ft_putstr_fd("cd: error retrieving current directory: ", 1);
			ft_putstr_fd("getcwd: cannot access parent ", 1);
			ft_putendl_fd("directories: No such file or directory", 1);
			wsh_change_pwd(wsh_list->wsh_envs, ".");
			*i = 1;
		}
		wsh_free((void*)tmp);
	}
	else
		if (!(ft_isin('/', wsh_token->wsh_param[0] + (
						ft_strlen(wsh_token->wsh_param[0]) - 1))))
			wsh_token->wsh_param[0] = ft_strjoin(wsh_token->wsh_param[0], "/");
	return ;
}

void	wsh_cd(t_wsh_list *wsh_list)
{
	char			*tmp;
	int				i;

	tmp = NULL;
	i = 0;
	if (wsh_list->ast_parsed->wsh_param)
	{
		tmp = wsh_list->ast_parsed->wsh_param[0];
		wsh_cd_dot(wsh_list, wsh_list->ast_parsed, &i);
		if (chdir(wsh_list->ast_parsed->wsh_param[0]) == ERROR)
		{
			wsh_cd_error(&tmp);
			g_status = 1;
			wsh_set_ret(wsh_list);
		}
	}
	else if (wsh_get_envar("HOME", wsh_list->wsh_envs))
		chdir(ft_strjoin(wsh_get_envar("HOME", wsh_list->wsh_envs), "/"));
	if (i == 0)
		wsh_change_pwd(wsh_list->wsh_envs, NULL);
	if (wsh_list->ast_parsed->std_out != 1 || wsh_list->ast_parsed->wsh_redi)
		exit(0);
	return ;
}
