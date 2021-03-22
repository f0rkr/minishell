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
	struct stat stats;
	int	fd;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	if (stat(path, &stats) == 0 && stats.st_mode & S_IXUSR)
		return ;
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

void		wsh_redi(t_wsh_list *wsh_list)
{
	int fd;
	t_wsh_redi *wsh_redi;

	fd = 0;
	wsh_redi = wsh_list->ast_parsed->wsh_redi;
	dup2(wsh_list->ast_parsed->std_in, 0);
	while (wsh_list->ast_parsed->wsh_redi)
	{
		if (ft_strncmp(wsh_list->ast_parsed->wsh_redi->type, ">>", 2) == 0)
		{
			if (fd)
				close(fd);
			fd = open(wsh_list->ast_parsed->wsh_redi->filename, O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(fd, 1);
		}
			
		if (ft_strncmp(wsh_list->ast_parsed->wsh_redi->type, ">", 2) == 0)
		{
			if (fd)
				close(fd);
			fd = open(wsh_list->ast_parsed->wsh_redi->filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
			dup2(fd, 1);
		}
		if (ft_strncmp(wsh_list->ast_parsed->wsh_redi->type, "<", 2) == 0)
		{
			if (fd)
				close(fd);
			fd = open(wsh_list->ast_parsed->wsh_redi->filename, O_RDONLY);
			dup2(fd, wsh_list->ast_parsed->std_in);
		}
		wsh_list->ast_parsed->wsh_redi = wsh_list->ast_parsed->wsh_redi->next;
	}
	wsh_list->ast_parsed->wsh_redi = wsh_redi;
}

void        wsh_execve(t_wsh_list *wsh_list)
{
    int     i;
    char    **cmd;
    char    *path;
    char    *tmp;
    char    **arr;
	int		pip[2];

    i = 0;
	arr = NULL;
	tmp = NULL;
	if (wsh_list->ast_parsed->std_out == 666)
	{
		pipe(pip);
		wsh_list->ast_parsed->std_out = pip[1];
		wsh_list->ast_parsed->next->std_in = pip[0];
	}
	if (wsh_list->ast_parsed->wsh_command[0] == '.')
		path = wsh_list->ast_parsed->wsh_command;
	else if (wsh_list->ast_parsed->wsh_command[0] == '<' || wsh_list->ast_parsed->wsh_command[0] == '>')
	{
		if (wsh_list->ast_parsed->wsh_command[0] == '>')
		{
			if (wsh_list->ast_parsed->wsh_param && wsh_list->ast_parsed->wsh_param[0] != NULL)
				open(wsh_list->ast_parsed->wsh_param[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
			if (wsh_list->ast_parsed->wsh_param && wsh_list->ast_parsed->wsh_param[1] != NULL)
			{
				ft_putstr_fd("wsh: ", 1);
				ft_putstr_fd(wsh_list->ast_parsed->wsh_param[1], 1);
				ft_putendl_fd(": command not found", 1);
			}
			if (!wsh_list->ast_parsed->wsh_param)
				ft_putendl_fd("wsh: syntax error near unexpected token `newline'", 1);
		}
		else
		{
			if (wsh_list->ast_parsed->wsh_param && wsh_list->ast_parsed->wsh_param[0] != NULL)
			{
				ft_putstr_fd("wsh: ", 1);
				ft_putstr_fd(wsh_list->ast_parsed->wsh_param[0], 1);
				ft_putendl_fd(": No such file or directory", 1);
			}
			else
				ft_putendl_fd("wsh: syntax error near unexpected token `newline'", 1);
		}
		return ;
	}
	else
	{
		while (wsh_list->wsh_envs && wsh_list->wsh_envs[i] && ft_strncmp(wsh_list->wsh_envs[i], "PATH=", 5) != 0)
			i++;
		cmd = ft_split(wsh_list->wsh_envs[i], ':');
		path = check_bin(cmd[0] + 5, wsh_list->ast_parsed->wsh_command);
		i = 0;
		while (wsh_list->ast_parsed->wsh_command && cmd[i] && path == NULL)
			path = check_bin(cmd[i++], wsh_list->ast_parsed->wsh_command);
		tmp = ft_strjoin(path, "/");
   		path = ft_strjoin(tmp, wsh_list->ast_parsed->wsh_command);
		wsh_free((void*) tmp);
		wsh_loop_free((void **)cmd);
	}
	arr = wsh_set_arr(path, wsh_list);
	if (path == NULL)
		path = cmd[0] + 5;
	i = fork();
	// i = 0;
	if (i == 0)
	{
		if (wsh_list->ast_parsed->wsh_redi)
			wsh_redi(wsh_list);
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
			execve(arr[0] , arr, wsh_list->wsh_envs);
			ft_error(path, wsh_list->ast_parsed->wsh_command);
			exit(1);
		}
	}
	else if (i > 0)
	{
		if (wsh_list->ast_parsed->std_out != 1)
			close(wsh_list->ast_parsed->std_out);
		if (wsh_list->ast_parsed->std_in != 0)
			close(wsh_list->ast_parsed->std_in);
	}
	if (arr[0] != NULL)
		wsh_loop_free((void **)arr);
	return ;
}