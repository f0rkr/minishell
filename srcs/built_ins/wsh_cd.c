/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:39:56 by mashad            #+#    #+#             */
/*   Updated: 2021/03/19 15:12:32 by mashad           ###   ########.fr       */
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

void	wsh_cd(t_wsh_list *wsh_list)
{
	char			*tmp;
	t_wsh_tokens	*wsh_token;

	tmp = NULL;
	wsh_token = wsh_list->ast_parsed;
	if (wsh_token->wsh_param)
	{
		tmp = wsh_token->wsh_param[0];
		if (ft_strncmp(wsh_token->wsh_param[0], ".", 2) != 0)
		{
			if (!(ft_isin('/', wsh_token->wsh_param[0] + (
							ft_strlen(wsh_token->wsh_param[0]) - 1))))
			{
				wsh_token->wsh_param[0] = ft_strjoin(wsh_token->wsh_param[0], "/");
			}
		}
		if (chdir(wsh_token->wsh_param[0]) != 0)
			if (opendir(wsh_token->wsh_param[0]) == NULL)
				wsh_cd_error(&tmp);
	}
	else if (wsh_get_envar("HOME", wsh_list->wsh_envs))
		chdir(ft_strjoin(wsh_get_envar("HOME", wsh_list->wsh_envs), "/"));
	if (wsh_token->std_out != 1 || wsh_token->wsh_redi)
		exit(0);
	return ;
}
