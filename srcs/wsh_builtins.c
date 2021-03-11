#include "minishell.h"

// void	wsh_builtins( t_wsh_tokens *wsh_token, t_wsh_list *wsh_list)
// {
	
// 	if (ft_strncmp(wsh_token->wsh_command, "echo", 5))
// 		wsh_echo(wsh_token);
// 	else if (ft_strncmp(wsh_token->wsh_command, "env", 4))
// 		wsh_env( wsh_list->wsh_envs );
// 	else if (ft_strncmp(wsh_token->wsh_command, "exit", 5))
// 		wsh_exit(wsh_list);
// 	else if (ft_strncmp(wsh_token->wsh_command, "export", 7))
// 		wsh_export( wsh_token, wsh_list );
// 	else if (ft_strncmp(wsh_token->wsh_command, "unset", 6))
// 		wsh_unset( wsh_token, wsh_list );
// 	else if (ft_strncmp(wsh_token->wsh_command, "cd", 3))
// 		wsh_cd( wsh_list );
// 	else if (ft_strncmp(wsh_token->wsh_command, "pwd", 4))
// 		wsh_pwd();
// }