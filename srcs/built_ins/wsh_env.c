/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:24:01 by oel-ouar          #+#    #+#             */
/*   Updated: 2021/03/29 12:23:59 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wsh_env(t_wsh_list *wsh_list)
{
	int		i;

	i = 0;
	while (wsh_list->wsh_envs[i] != 0)
	{
		if (wsh_findeq(wsh_list->wsh_envs[i]))
			ft_putendl_fd(wsh_list->wsh_envs[i], 1);
		i++;
	}
	g_tab[0] = 0;
	if (wsh_list->ast_parsed->std_out != 1 || wsh_list->ast_parsed->wsh_redi)
		exit(0);
	return ;
}
