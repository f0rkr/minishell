#include "minishell.h"

char	*check_bin(char *cmd, char *command)
{
	DIR				*folder;
	struct dirent	*entry;
	char			*path;

	path = NULL;
	folder = opendir(cmd);
	if (!folder)
		return (NULL);
	entry = readdir(folder);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, command, ft_strlen(command) + 1) == 0)
			path = cmd;
		entry = readdir(folder);
	}
	closedir(folder);
	return (path);
}

char	**wsh_set_arr(char *path, t_wsh_list *list)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = 1;
	arr = (char **) malloc(sizeof(char *) * 1024);
	if (!arr)
		return (NULL);
	arr[0] = path;
	while (list->ast_parsed->wsh_arg && list->ast_parsed->wsh_arg[i])
		arr[j++] = ft_strdup(list->ast_parsed->wsh_arg[i++]);
	i = 0;
	while (list->ast_parsed->wsh_param && list->ast_parsed->wsh_param[i])
		arr[j++] = ft_strdup(list->ast_parsed->wsh_param[i++]);
	arr[j] = 0;
	return (arr);
}

int	ft_error(char *path, char *command)
{
	DIR			*folder;
	struct stat	stats;
	int			fd;
	int			ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	if (stat(path, &stats) == 0 && stats.st_mode & S_IXUSR)
		return (0);
	wsh_error_norm(fd, path, command, folder);
	if ((path && ft_strchr(path, '/') == NULL) || (fd == -1 && folder == NULL))
		ret = 127;
	else
		ret = 126;
	if (folder)
		closedir(folder);
	close(fd);
	return (ret);
}

int	wsh_redi(t_wsh_list *wsh_list)
{
	int			fd;
	t_wsh_redi	*wsh_redi;

	fd = 0;
	wsh_redi = wsh_list->ast_parsed->wsh_redi;
	dup2(wsh_list->ast_parsed->std_in, 0);
	while (wsh_list->ast_parsed->wsh_redi)
	{
		wsh_red_help(wsh_list, fd);
		if (!(wsh_red_helper(wsh_list, fd)))
			return (0);
		wsh_list->ast_parsed->wsh_redi = wsh_list->ast_parsed->wsh_redi->next;
	}
	wsh_list->ast_parsed->wsh_redi = wsh_redi;
	return (1);
}

void	wsh_execve(t_wsh_list *wsh_list)
{
	int		i;
	char	*path;
	char	**arr;

	i = 1;
	arr = NULL;
	path = NULL;
	wsh_pipe(wsh_list, &path);
	if (wsh_list->ast_parsed->wsh_command[0] == '<'
		|| wsh_list->ast_parsed->wsh_command[0] == '>')
	{
		wsh_redi_out(wsh_list);
		wsh_redi_in(wsh_list);
		return ;
	}
	else if (path == NULL)
		wsh_path(wsh_list, &path);
	arr = wsh_set_arr(path, wsh_list);
	g_tab[1] = fork();
	if (g_tab[1] == 0)
		wsh_child_exec(wsh_list, i, arr, path);
	else if (g_tab[1] > 0)
		wsh_exec_parent(wsh_list);
	wsh_loop_free(arr);
	return ;
}
