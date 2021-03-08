#include "minishell.h"


char		*check_bin(char *cmd, char *command)
{
	DIR				*folder;
	struct dirent	*entry;
	char			*path;

	path = NULL;
	folder = opendir(cmd);
	if (!folder)
		return (NULL);
	while ((entry = readdir(folder)))
	{
		if (ft_strncmp(entry->d_name, command, ft_strlen(command) + 1) == 0)
			path = cmd;
	}
	closedir(folder);
	return (path);
}

char        **wsh_set_arr(char *path, t_wsh_list *wsh_list)
{
    int 	i;
    int 	j;
	char	**arr;

    i = 0;
    j = 1;
	if (!(arr = (char **) malloc(sizeof(char *) * 1024)))
		return (NULL);
    arr[0] = path;
    while (wsh_list->ast_parsed->wsh_arg && wsh_list->ast_parsed->wsh_arg[i])
        arr[j++] = ft_strdup(wsh_list->ast_parsed->wsh_arg[i++]);
	i = 0;
    while (wsh_list->ast_parsed->wsh_param && wsh_list->ast_parsed->wsh_param[i])
        arr[j++] = ft_strdup(wsh_list->ast_parsed->wsh_param[i++]);
    arr[j] = NULL;
	return (arr);
}

void		ft_error(char *path, char *command)
{
	DIR	*folder;
	int	fd;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	if (fd == -1)
		path = command;
	ft_putstr_fd("wsh: ", 2);
	ft_putstr_fd(path, 2);
	if ((ft_strchr(path, '/')) == NULL)
		ft_putendl_fd(": command not found", 2);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", 2);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", 2);
	if (folder)
		closedir(folder);
	close(fd);
}

void        wsh_execve(t_wsh_list *wsh_list)
{
    int     i;
    char    **cmd;
    char    *path;
    char    *tmp;
    char    **arr;

    i = 0;
	arr = NULL;
	if ((char)wsh_list->ast_parsed->wsh_command[0] == '.')
	{
		tmp = ft_strjoin(wsh_get_envar("PWD", wsh_list->wsh_envs), "/");
		path = ft_strjoin(tmp, (wsh_list->ast_parsed->wsh_command + 2));
		wsh_free((void*)tmp);
	}
	else
	{
		while (wsh_list->wsh_envs && wsh_list->wsh_envs[i] && ft_strncmp(wsh_list->wsh_envs[i], "PATH=", 5) != 0)
			i++;
		cmd = ft_split(wsh_list->wsh_envs[i], ':');
		path = check_bin(cmd[0] + 5, wsh_list->ast_parsed->wsh_command);
		i = 50;
		while (wsh_list->ast_parsed->wsh_command && cmd[i] && path == NULL)
			path = check_bin(cmd[i++], wsh_list->ast_parsed->wsh_command);
		tmp = ft_strjoin(path, "/");
   		path = ft_strjoin(tmp, wsh_list->ast_parsed->wsh_command);
		wsh_free((void*) tmp);
		wsh_loop_free((void **)cmd);
	}
	if (path == NULL)
		path = cmd[0] + 5;
    arr = wsh_set_arr(path, wsh_list);
	i = fork();
	if (i == 0)
	{  
        if (execve(arr[0] , arr, wsh_list->wsh_envs) == -1)
		{
			ft_error(path, wsh_list->ast_parsed->wsh_command);
            exit(1);
		}
	}
	else
		waitpid(i ,0 ,0);
	
	wsh_loop_free((void **)arr);
	return ;
}
