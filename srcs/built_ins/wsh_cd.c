/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:39:56 by mashad            #+#    #+#             */
/*   Updated: 2021/03/26 15:23:23 by oel-ouar         ###   ########.fr       */
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

void	wsh_cd_dot(t_wsh_list *wsh_list, int *i)
{
	if (!ft_strncmp(wsh_list->ast_parsed->wsh_param[0], ".", 2))
	{
		if (opendir(ft_strjoin(wsh_get_envar("PWD", wsh_list->wsh_envs), "/")) == NULL)
		{
			ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent", 1);
			ft_putendl_fd(" directories: No such file or directory", 1);
			wsh_change_pwd(wsh_list->wsh_envs, ".");
			*i = 1;
		}
	}
	else if (ft_strncmp(wsh_list->ast_parsed->wsh_param[0], ".", 2) != 0)
	{
		if (!(ft_isin('/', wsh_list->ast_parsed->wsh_param[0] + (
						ft_strlen(wsh_list->ast_parsed->wsh_param[0]) - 1))))
		{
			wsh_list->ast_parsed->wsh_param[0] = ft_strjoin(wsh_list->ast_parsed->wsh_param[0], "/");
		}
	}
}

void	wsh_cd(t_wsh_list *wsh_list)
{
	char			*tmp;
	t_wsh_tokens	*wsh_token;
	int				i;

	tmp = NULL;
	i = 0;
	wsh_token = wsh_list->ast_parsed;
	if (wsh_token->wsh_param)
	{
		tmp = wsh_token->wsh_param[0];
		wsh_cd_dot(wsh_list, &i);
		if (chdir(wsh_token->wsh_param[0]) != 0)
		{
			if (opendir(wsh_token->wsh_param[0]) == NULL)
				wsh_cd_error(&tmp);
			g_status = 1;
			wsh_set_ret(wsh_list);
		}	
	}
	else if (wsh_get_envar("HOME", wsh_list->wsh_envs))
		chdir(ft_strjoin(wsh_get_envar("HOME", wsh_list->wsh_envs), "/"));
	if (i == 0)
		wsh_change_pwd(wsh_list->wsh_envs, NULL);
	if (wsh_token->std_out != 1 || wsh_token->wsh_redi)
		exit(0);
	return ;
}
