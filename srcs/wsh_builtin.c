#include "minishell.h"

char	*ft_lower(char *string)
{
	char	*str;
	int		c_j;

	c_j = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(string) + 1);
	while (string[c_j] != EOL)
	{
		str[c_j] = ft_tolower(string[c_j]);
		c_j++;
	}
	str[c_j] = EOL;
	return (str);
}

int	ft_isbuiltin(const char *command)
{
	static char		builin[7][10] = {"echo", "cd", "pwd",
		"exit", "export", "unset", "env"};
	int				i;

	i = 0;
	while (ft_strncmp(command, builin[i], ft_strlen(builin[i])) != 0)
		i++;
	if (i == 7)
		return (0);
	return (1);
}

int	wsh_exec_builtin(t_wsh_list *wsh_list)
{
	if (!ft_strncmp(wsh_list->ast_parsed->wsh_command, "pwd", 4))
		wsh_pwd(wsh_list);
	if (!ft_strncmp(wsh_list->ast_parsed->wsh_command, "env", 4))
		wsh_env(wsh_list);
	if (!ft_strncmp(wsh_list->ast_parsed->wsh_command, "echo", 5))
		wsh_echo(wsh_list->ast_parsed);
	if (!ft_strncmp(wsh_list->ast_parsed->wsh_command, "export", 7))
		wsh_export(wsh_list->ast_parsed, wsh_list);
	if (!ft_strncmp(wsh_list->ast_parsed->wsh_command, "exit", 5))
		wsh_exit(wsh_list);
	if (!ft_strncmp(wsh_list->ast_parsed->wsh_command, "cd", 3))
		wsh_cd(wsh_list);
	if (!ft_strncmp(wsh_list->ast_parsed->wsh_command, "unset", 6))
		wsh_unset(wsh_list->ast_parsed, wsh_list);
	return (0);
}
