#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <sys/stat.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <sys/errno.h>
# include <string.h>
# include <fcntl.h>

/*
** DEFINE SPECIAL CHARACTERS
*/

# define SPACE		' '
# define PIPE		'|'
# define AND		';'
# define OUTRID		'>'
# define INRID		'<'
# define DRID		">>"
# define ESC		'\\'
# define DQUOTE		'\"'
# define SQUOTE		'\''
# define V		'$'
# define EOL		'\0'
# define ERROR 		-1
# define INIT 		0
# define STDIN		0
# define STDOUT		1
# define EXIT 		1
# define BUILTIN	2
# define CMD		3
# define LOOP		4
# define ENDEXEC	5
# define REDIREC	6
# define BUFFER_SIZE 	1024

/*
** WESH SHELL DEFAULT COLORS
*/

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

/*
** WESH SIGNALS
*/
# define SIGHUP  1
# define SIGINT  2
# define SIGQUIT 3
# define SIGILL  4
# define SIGTRAP 5
# define SIGABRT 6

/*
** WESH SHELL STRUCT
*/
int	g_tab[2];

typedef struct s_wsh_redirection
{
	char						*filename;
	char						*type;
	struct s_wsh_redirection	*next;
}				t_wsh_redi;

typedef struct s_wsh_tokens
{
	char					*wsh_command;
	char					**wsh_arg;
	char					**wsh_param;
	int						type;
	int						std_in;
	int						std_out;
	t_wsh_redi				*wsh_redi;
	struct s_wsh_tokens		*next;
}		t_wsh_tokens;

typedef struct s_wsh_list
{
	t_wsh_tokens		*ast_parsed;
	char				*string;
	char				*tmp;
	int					garbage_flag;
	char				**wsh_history;
	int					history_counter;
	int					history_len;
	char				**wsh_envs;
}		t_wsh_list;

/*
** Functions Prototype
*/

int				get_next_line(int fd, char **line);
int				wsh_searchenvx(char **wsh_envs, char *var);
void			wsh_echo(t_wsh_tokens *whs_token);
void			wsh_env(t_wsh_list *wsh_list);
void			wsh_exit(t_wsh_list *wsh_list);
void			wsh_cd(t_wsh_list *wsh_list);
void			wsh_pwd(t_wsh_list *wsh_list);
int				wsh_loop(t_wsh_list *wsh_list);
void			wsh_unset(t_wsh_tokens *wsh_token, t_wsh_list *wsh_list);
void			wsh_export(t_wsh_tokens *wsh_token, t_wsh_list *wsh_list);
void			wsh_builtins(t_wsh_tokens *wsh_token, t_wsh_list *wsh_list);
char			*wsh_read(t_wsh_list *wsh_list, int *garbage_flag);
t_wsh_tokens	*wsh_parse(t_wsh_list *wsh_list, char *cmd);
void			wsh_exec(t_wsh_list *wsh_list);
int				ft_isbuiltin(const char *command);
int				wsh_exec_builtin(t_wsh_list *wsh_list);
int				wsh_garbageCollector(t_wsh_list *wsh_list);
t_wsh_tokens	*wsh_token_init(void);
int				searcheq(char *str);
void			wsh_free(char **data);
void			wsh_loop_free(char **data);
char			*before_eq(char *str);
void			wsh_execve(t_wsh_list *wsh_list);
char			*wsh_get_envar(char *s, char **env);
int				wsh_tab_length(char **tabb);
int				wsh_findeq(char *var);
int				wsh_removevarandadd(char **wsh_envs, char *var, int c_p);
t_wsh_redi		*wsh_redi_init(void);
int				wsh_first_char(char *string);
char			*wsh_escape(t_wsh_list *wsh_list, char pipe[1024]);
void			wsh_export_error(char *param);
void			wsh_init_var(int *i, int *j);
int				expo(char *param, char **envs, char **c_var, int *c_j);
void			handle_sigin(int sig);
void			handle_quit(int sig);
void			*wsh_fillargs(t_wsh_list *wsh_list, t_wsh_tokens *wsh_token,
					char wsh_args[][1024], int *position);
int				wsh_expo(char *param, char **envs, char **c_var, int *c_j);
void			wsh_red_help(t_wsh_list *wsh_list, int fd);
int				wsh_red_helper(t_wsh_list *wsh_list, int fd);
void			wsh_error_norm(int fd, char *path, char *command, DIR *folder);
void			wsh_child_exec(t_wsh_list *wsh_list,
					int i, char **arr, char *path);
int				wsh_redi(t_wsh_list *wsh_list);
int				ft_error(char *path, char *command);
void			wsh_path(t_wsh_list *wsh_list, char **path);
char			*check_bin(char *cmd, char *command);
void			wsh_pipe(t_wsh_list *wsh_list, char **path);
void			wsh_redi_in(t_wsh_list *wsh_list);
void			wsh_redi_out(t_wsh_list *wsh_list);
void			wsh_exec_parent(t_wsh_list *wsh_list);
int				string_checker(char *string);

#endif
