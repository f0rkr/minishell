#include "minishell.h"

int		wsh_removevarandadd(char **wsh_envs, char *var, int c_p)
{

	wsh_free((void *)wsh_envs[c_p]);
	wsh_envs[c_p] = NULL;
	wsh_envs[c_p] = ft_strdup(var);
	return (0);
}

int		wsh_findeq(char *var)
{
	int		c_i;

	c_i = 0;
	while (var && var[c_i] != EOL && var[c_i] != '=')
		c_i++;
	if (var[c_i] == '=')
		return (c_i);
	return (0);
}

int		wsh_searchenvx(char **wsh_envs, char *var)
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
		if ((ft_strncmp(c_env, var, ft_strlen(var)+1) == 0) 
		|| (ft_strncmp(test, var, ft_strlen(var)) == 0))
			return (c_i);
		wsh_free((void *)c_env);
		c_env = NULL;
		c_i++;
	}
	return (0);
}

void	wsh_export_only(t_wsh_list *wsh_list)
{
	int c_i;
	int c_j;
	int c_k;

	c_i = 0;
	c_j = 0;
	c_k = 0;
	while (wsh_list->wsh_envs[c_i])
	{
		c_k = 0;
		c_j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (wsh_list->wsh_envs[c_i][c_j] != '\0')
		{
			ft_putchar_fd(wsh_list->wsh_envs[c_i][c_j], 1);
			if (wsh_list->wsh_envs[c_i][c_j] == '=')
			{
				c_k = 1;
				ft_putchar_fd(DQUOTE, 1);
			}
			c_j++;
		}
		if (c_k == 1)
			ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		c_i++;
	}
}

int		wsh_export_valid(char *param)
{
	int i;
	int j;

	i = 0;
	if (wsh_findeq(param))
		j = wsh_findeq(param);
	else
		j = ft_strlen(param);
	while (i < j)
	{
		if (!ft_isalpha(param[i]) && !ft_isdigit(param[i]))
			if (ft_isalpha(param[i + 1]))
				return (1);
		i++;	
	}
	return (0);
}

void	wsh_export(t_wsh_tokens *wsh_token, t_wsh_list *wsh_list)
{
	int		c_i;
	int		c_j;
	int		c_p;
	char	*c_var;

	c_i = 0;
	c_p = 0;
	c_j = 0;
	c_var = NULL;
	if (!wsh_token->wsh_param)
		wsh_export_only(wsh_list);
	else if (!ft_isalpha(wsh_token->wsh_param[0][0]))
	{
		ft_putstr_fd("wsh : export: `", 1);
		ft_putstr_fd(wsh_token->wsh_param[0], 1);
		ft_putendl_fd("': not a valid identifier", 1);
	}
	else
	{
		while (wsh_list->wsh_envs[c_j] != NULL)
			c_j++;
		while (wsh_token->wsh_param && wsh_token->wsh_param[c_i] != NULL)
		{
			if (wsh_export_valid(wsh_token->wsh_param[c_i]))
			{
				ft_putstr_fd("wsh : export: `", 1);
				ft_putstr_fd(wsh_token->wsh_param[c_i], 1);
				ft_putendl_fd("': not a valid identifier", 1);
			}
			else if (wsh_findeq(wsh_token->wsh_param[c_i]))
			{
				c_var = ft_substr(wsh_token->wsh_param[c_i], 0, wsh_findeq(wsh_token->wsh_param[c_i]));
				if (((c_p = wsh_searchenvx(wsh_list->wsh_envs, c_var)) && wsh_token->wsh_param[c_i]))
					wsh_removevarandadd(wsh_list->wsh_envs, wsh_token->wsh_param[c_i], c_p);
				else
				{
					wsh_list->wsh_envs[c_j++] = ft_strdup(wsh_token->wsh_param[c_i]);
					wsh_list->wsh_envs[c_j] = NULL;
				}
			}
			else
			{
				c_var = ft_strdup(wsh_token->wsh_param[c_i]);
				if ((c_p = wsh_searchenvx(wsh_list->wsh_envs, c_var)) && wsh_token->wsh_param[c_i])
					break ;
				else
				{
					wsh_list->wsh_envs[c_j++] = ft_strdup(wsh_token->wsh_param[c_i]);
					wsh_list->wsh_envs[c_j] = NULL;
				}
			}
			wsh_free((void *)c_var);
			c_var = NULL;
			c_i++;
		}
	}
	if (wsh_list->ast_parsed->std_out != 1 || wsh_list->ast_parsed->wsh_redi)
		exit(0) ;
	else
		return ;
}
