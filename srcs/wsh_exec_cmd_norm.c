#include "minishell.h"

void	wsh_red_help(t_wsh_list *wsh_list, int fd)
{
	if (ft_strncmp(wsh_list->ast_parsed->wsh_redi->type, ">>", 2) == 0)
	{
		if (fd)
			close(fd);
		fd = open(wsh_list->ast_parsed->wsh_redi->filename,
				O_RDWR | O_CREAT | O_APPEND, 0644);
		dup2(fd, 1);
	}
	if (ft_strncmp(wsh_list->ast_parsed->wsh_redi->type, ">", 2) == 0)
	{
		if (fd)
			close(fd);
		fd = open(wsh_list->ast_parsed->wsh_redi->filename,
				O_CREAT | O_TRUNC | O_RDWR, 0644);
		dup2(fd, 1);
	}
}

int	wsh_red_helper(t_wsh_list *wsh_list, int fd)
{
	if (ft_strncmp(wsh_list->ast_parsed->wsh_redi->type, "<", 2) == 0)
	{
		if (fd)
			close(fd);
		fd = open(wsh_list->ast_parsed->wsh_redi->filename, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("wsh: ", 0);
			ft_putstr_fd(wsh_list->ast_parsed->wsh_redi->filename, 0);
			ft_putendl_fd(": No such file or directory", 0);
			return (0);
		}
		dup2(fd, wsh_list->ast_parsed->std_in);
	}
	return (1);
}

void	wsh_error_norm(int fd, char *path, char *command, DIR *folder)
{
	int	i;

	i = 0;
	ft_putstr_fd("wsh: ", 2);
	if (path && !(ft_strncmp(path, "error", 6)))
	{
		ft_putstr_fd(command, 2);
		ft_putendl_fd(": No such file or directory", 2);
		i = 1;
	}
	else if (fd == -1)
		path = command;
	if (i == 0)
		ft_putstr_fd(path, 2);
	if ((ft_strchr(path, '/')) == NULL && i == 0)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && folder == NULL && i == 0)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && folder != NULL && i == 0)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && folder == NULL && i == 0)
		ft_putendl_fd(": Permission denied", 2);
}

void	wsh_child_exec(t_wsh_list *wsh_list, int i, char **arr, char *path)
{
	int	ret;

	ret = 0;
	if (wsh_list->ast_parsed->wsh_redi)
		i = wsh_redi(wsh_list);
	if (wsh_list->ast_parsed->std_out != 1)
	{
		close(wsh_list->ast_parsed->next->std_in);
		dup2(wsh_list->ast_parsed->std_out, 1);
	}
	if (wsh_list->ast_parsed->std_in != 0)
		dup2(wsh_list->ast_parsed->std_in, 0);
	if (wsh_list->ast_parsed->type == BUILTIN)
		wsh_exec_builtin(wsh_list);
	else
	{
		if (i == 1)
		{
			execve(arr[0], arr, wsh_list->wsh_envs);
			ret = ft_error(path, wsh_list->ast_parsed->wsh_command);
			exit(ret);
		}
		exit(1);
	}
}

void	wsh_path(t_wsh_list *wsh_list, char **path)
{
	int		i;
	char	**cmd;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (wsh_list->wsh_envs && wsh_list->wsh_envs[i]
		&& ft_strncmp(wsh_list->wsh_envs[i], "PATH=", 5) != 0)
		i++;
	cmd = ft_split(wsh_list->wsh_envs[i], ':');
	if (wsh_list->ast_parsed->wsh_command[0] == '/' && !(*path))
		*path = ft_strdup(wsh_list->ast_parsed->wsh_command);
	else if (cmd)
	{
		*path = check_bin(cmd[0] + 5, wsh_list->ast_parsed->wsh_command);
		i = 0;
		while (wsh_list->ast_parsed->wsh_command && cmd[i] && *path == NULL)
			*path = check_bin(cmd[i++], wsh_list->ast_parsed->wsh_command);
		tmp = ft_strjoin(*path, "/");
		*path = ft_strjoin(tmp, wsh_list->ast_parsed->wsh_command);
	}
	else if (*path == NULL && !cmd)
		*path = ft_strdup("error");
	free(tmp);
	wsh_loop_free(cmd);
}
