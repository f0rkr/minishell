/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-ouar <oel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 12:39:19 by oel-ouar          #+#    #+#             */
/*   Updated: 2021/04/07 13:11:47 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wsh_searchenvx(char **wsh_envs, char *var)
{
	int		c_i;
	int		c_j;
	char	*c_env;
	char	*test;

	c_j = 0;
	c_i = 0;
	c_env = NULL;
	while (wsh_envs && wsh_envs[c_i] != NULL)
	{
		test = wsh_envs[c_i];
		c_env = ft_substr(wsh_envs[c_i], 0, wsh_findeq(wsh_envs[c_i]));
		if ((ft_strncmp(c_env, var, ft_strlen(var) + 1) == 0)
			|| (ft_strncmp(test, var, ft_strlen(var)) == 0))
		{
			free(c_env);
			return (c_i);
		}
		free(c_env);
		c_i++;
	}
	return (0);
}

void	wsh_export_only(t_wsh_list *wsh_list)
{
	int		c_i;
	int		c_j;
	int		c_k;

	c_i = -1;
	while (wsh_list->wsh_envs[++c_i])
	{
		wsh_init_var(&c_j, &c_k);
		ft_putstr_fd("declare -x ", 1);
		while (wsh_list->wsh_envs[c_i][c_j] != EOL)
		{
			ft_putchar_fd(wsh_list->wsh_envs[c_i][c_j], 1);
			if (wsh_list->wsh_envs[c_i][c_j++] == '=')
			{
				c_k = 1;
				ft_putchar_fd(DQUOTE, 1);
			}
		}
		if (c_k == 1)
			ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
	}
	g_tab[0] = 0;
}

void	wsh_export_valid(char *param)
{
	int	i;
	int	j;

	i = 0;
	if (wsh_findeq(param))
		j = wsh_findeq(param);
	else
		j = ft_strlen(param);
	while (i < j)
	{
		if (!ft_isalpha(param[i]) && !ft_isdigit(param[i]))
			if (ft_isalpha(param[i + 1]))
				wsh_export_error(param);
		i++;
	}
	g_tab[0] = 0;
}

void	wsh_remove_spaces(char *param)
{
	int		c_i;
	int		c_j;
	char	*tmp;

	c_i = 0;
	c_j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(param) + 1));
	if (!tmp)
		return ;
	while (param[c_i] != EOL)
	{
		if (param[c_i] == ' ')
		{
			tmp[c_j++] = param[c_i++];
			while (param[c_i] == ' ' && param[c_i] != EOL)
				c_i++;
		}
		tmp[c_j++] = param[c_i++];
	}
	tmp[c_j] = '\0';
	ft_strlcpy(param, tmp, ft_strlen(tmp) + 1);
	free(tmp);
	return ;
}

void	wsh_export(t_wsh_tokens *token, t_wsh_list *wsh_list)
{
	int		c_i;
	int		c_j;
	char	*c_var;

	c_i = -1;
	c_j = 0;
	c_var = NULL;
	if (!token->wsh_param)
		wsh_export_only(wsh_list);
	else if (!ft_isalpha(token->wsh_param[0][0]))
		wsh_export_error(token->wsh_param[0]);
	else
	{
		c_j = wsh_tab_length(wsh_list->wsh_envs);
		while (token->wsh_param && token->wsh_param[++c_i] != NULL)
		{
			wsh_remove_spaces(token->wsh_param[c_i]);
			wsh_export_valid(token->wsh_param[c_i]);
			if (expo(token->wsh_param[c_i], wsh_list->wsh_envs, &c_var, &c_j))
				break ;
		}
	}
	if (wsh_list->ast_parsed->std_out != 1 || wsh_list->ast_parsed->wsh_redi)
		exit(0);
	return ;
}
