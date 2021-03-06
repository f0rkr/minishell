#ifndef MINISHELL_H
# define MINISHELL_H



# include "../libft/libft.h"
# include "parsing.h"
# include <sys/stat.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <sys/errno.h>

/*
** DEFINE SPECIAL CHARACTERS
*/
# define SPACE			' '
# define PIPE			'|'
# define AND			';'
# define OUTRID			'>'
# define INRID			'<'
# define DRID			">>"
# define ESC			'\\'
# define DQUOTE			'\"'
# define SQUOTE			'\''
# define VAR			'$'
# define EOL			'\0'
# define ERROR 			-1
# define INIT 			0
# define STDIN			0
# define STDOUT			1
# define EXIT 			1
# define BUILTIN		2
# define CMD			3
# define LOOP			4
# define ENDEXEC		5
# define BUFFER_SIZE 	1024

/*
** WESH SHELL STRUCT
*/


typedef struct		s_wsh_tokens
{
	int						type;
	void					*wsh_command;
	char					**wsh_arg;
	char					**wsh_param;
	int						std_in;
	int						std_out;
	struct s_wsh_tokens		*next;
}					t_wsh_tokens;

typedef struct		s_wsh_list
{
	t_wsh_tokens	*ast_parsed;
	char			*string;
	int				garbage_flag;
	char			**wsh_envs;
}					t_wsh_list;

/*
** Functions Prototype
*/
int				get_next_line(int fd, char **line);
void			wsh_echo(t_wsh_tokens	*whs_token);
void			wsh_env(char **env);
void			wsh_exit(t_wsh_list *wsh_list);
void			wsh_cd(t_wsh_tokens *wsh_token);
void			wsh_pwd(void);
void			wsh_unset(t_wsh_tokens *wsh_token, t_wsh_list *wsh_list);
void			wsh_export(t_wsh_tokens *wsh_token, t_wsh_list *wsh_list);
void			wsh_builtins( t_wsh_tokens *wsh_token ,t_wsh_list *wsh_list);
char    		*wsh_read( int *garbage_flag );
t_wsh_tokens	*wsh_parse( char *cmd );
void			*wsh_exec( t_wsh_list *wsh_list );
int				ft_isbuiltin(const char *command);
int				wsh_exec_builtin(t_wsh_list *wsh_list);
int     		wsh_garbageCollector(t_wsh_list *wsh_list);
t_wsh_tokens	*wsh_token_init();
int				searcheq(char *str);
void			wsh_free(void *data);
char			**ft_tmparr(char **env, int i);
char			*before_eq(char *str);
#endif