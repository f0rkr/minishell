#include "minishell.h"
int		handle_sigd(t_wsh_list *wsh_list, char **line, char **line_tmp)
{
	int		c_i;
	char	*tmp;
	c_i = 0;
	tmp = NULL;
	if (line[0][0] != EOL || line_tmp[0][0] != EOL)
	{
		tmp = *line;
		*line = ft_strjoin(*line_tmp, *line);
		wsh_free((void *)*line_tmp);
		return (EXIT);
	}
	else
	{
		ft_putstr_fd("exit", 0);
		wsh_free((void *) *line);
		wsh_garbageCollector(wsh_list);
		exit(0);
	}
}
char	*wsh_read(t_wsh_list *wsh_list, int *garbage_flag, char **tmp)
{
	char	*string;
	char	buff[4029];
	int		ret;
	getcwd(buff, 4029);
	ft_putstr_fd("\x1B[36mwsh\x1B[0m\x1B[34m :: \x1B[0m", 1);
	ft_putstr_fd("\x1B[32m", 1);
	ft_putstr_fd(buff, 1);
	ft_putstr_fd("\x1B[0m\x1B[31m » \x1B[0m", 1);
	ret = get_next_line(0, &string);
	if (ret == ERROR)
	{
		*garbage_flag = ERROR;
		return (NULL);
	}
	if (ret == 0)
		handle_sigd(wsh_list, &string, tmp);
	return (string);
}