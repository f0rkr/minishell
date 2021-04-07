/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:53:37 by mashad            #+#    #+#             */
/*   Updated: 2021/04/07 12:58:09 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

extern int	wsh_scan_commands(char *str, const char *string, int pipe);
extern int	is_and(const char *str, int p, int q_flag[2], int pipe);
extern int	wsh_tokenizer(char cmd[][1024], char *string, int pipe);
int			wsh_is_closed(char *string, int pos, char c);
char		*ft_lowerit(char *string);
int			ft_isubuiltin(const char *command);
void		wsh_command_norm(char *str, char *new_str, int *c_i, int *c_k);
extern int	ft_isspecial(char c);
extern int	wsh_is_redirection(char *c_r);
char		*wsh_escape(t_wsh_list *t_wsh_list, char pipe[1024]);
void		wsh_stick_redi(t_wsh_tokens *wsh_token, char *string);
int			isesc(char *string, int pos);
int			wsh_scan_help(char *str, int c_c, int q[2], int flag);
void		wsh_read_dquote_help(t_wsh_list *l, int *pos, int c_i);
void		wsh_esc_help(t_wsh_list *l, char *newpipe, int *c_j, int i);
void		wsh_redirection_dup(t_wsh_tokens *wsh_token,
				char string[][1024], int *c_j, int *c_n);
int			ft_issi(char c);
char		*wsh_escape(t_wsh_list *wsh_list, char *pipe);
void		wsh_process_quotes(t_wsh_list *wsh_list,
				char newstring[1024], int *pos, int *c_j);
void		wsh_read_dquote(t_wsh_list *l,
				char newstring[1024], int *pos, int *c_j);
void		wsh_read_squote(t_wsh_list *l,
				char newstring[1024], int *pos, int *c_j);
void		wsh_replacevar(t_wsh_list *l,
				char newstring[1024], int *c_pos, int *c_j);
void		wsh_remove_pointer(char string[][1024], char *str);
void		wsh_fill_redirection(t_wsh_tokens *wsh_token, char string[][1024]);
void		wsh_cd_home(char *tmp);
#endif
