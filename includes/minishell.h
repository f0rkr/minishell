#ifndef MINISHELL_H
# define MINISHELL_H

# define INIT 0
# define ERROR -1
# define EXIT 0
# define BUFFER_SIZE 1024

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

/*
** WESH SHELL STRUCT
*/


typedef struct		s_wsh_tokens
{
	int				type;
	void			*wsh_command;
	char			*wsh_arg;
	char			*wsh_param;
	int				std_in;
	int				std_out;
	struct s_list	*next;
}					t_wsh_tokens;

typedef struct		s_wsh_list
{
	void			*ast_parsed;
	char			*string;
	int				garbage_flag;
	t_wsh_tokens	wsh_tokens;
}					t_wsh_list;

/*
** Functions Prototype
*/
int		get_next_line(int fd, char **line);
char    *wsh_read( int *garbage_flag );
void	*wsh_parse( char *cmd );
void	*wsh_exec( void *ast_parsed );
int     wsh_garbageCollector(t_wsh_list *wsh_list);

#endif