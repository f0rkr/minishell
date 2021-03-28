/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_export_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:43:08 by oel-ouar          #+#    #+#             */
/*   Updated: 2021/03/28 16:43:18 by oel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wsh_export_error(char *param, t_wsh_list *wsh_list)
{
	ft_putstr_fd("wsh : export: `", 1);
	ft_putstr_fd(param, 1);
	ft_putendl_fd("': not a valid identifier", 1);
	g_status = 1;
	wsh_set_ret(wsh_list);
	return ;
}

int	wsh_findeq(char *var)
{
	int		c_i;

	c_i = 0;
	while (var && var[c_i] != EOL && var[c_i] != '=')
		c_i++;
	if (var[c_i] == '=')
		return (c_i);
	return (0);
}

int	wsh_removevarandadd(char **wsh_envs, char *var, int c_p)
{
	wsh_free((void *)wsh_envs[c_p]);
	wsh_envs[c_p] = NULL;
	wsh_envs[c_p] = ft_strdup(var);
	return (0);
}

void	wsh_init_var(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

int	wsh_expo(char *param, char **envs, char **c_var, int *c_j)
{
	int	c_p;

	c_p = 0;
	if (!wsh_findeq(param))
	{
		*c_var = ft_strdup(param);
		c_p = wsh_searchenvx(envs, *c_var);
		if (c_p && param)
			return (1);
		else
		{
			envs[(*c_j)++] = ft_strdup(param);
			envs[*c_j] = NULL;
		}
	}
	return (0);
}

int	expo(char *param, char **envs, char **c_var, int *c_j)
{
	int	c_p;

	c_p = 0;
	if (wsh_findeq(param))
	{
		*c_var = ft_substr(param, 0, wsh_findeq(param));
		c_p = wsh_searchenvx(envs, *c_var);
		if (c_p && param)
			wsh_removevarandadd(envs, param, c_p);
		else
		{
			envs[(*c_j)++] = ft_strdup(param);
			envs[*c_j] = NULL;
		}
	}
	if (wsh_expo(param, envs, c_var, c_j))
		return (1);
	if (*c_var != NULL && *c_var[0] != '\0')
		wsh_free((void *)*c_var);
	return (0);
}
