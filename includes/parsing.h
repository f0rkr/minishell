/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:53:37 by mashad            #+#    #+#             */
/*   Updated: 2021/01/08 11:57:47 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

extern int	wsh_scan_commands(char *str, const char *string, int pipe);
extern int	is_and(const char *str, int p, int q_flag, int pipe);
extern int	wsh_tokenizer(char cmd[][1024], char *string, int pipe);
extern int	wsh_check(char *c_r);
extern int	ft_isspecial(char *c, int c_pos);
extern int	wsh_is_redirection(char *c_r);
extern int	wsh_quotesremove(char *c, int c_sq, int c_dq, int c_p);
void		wsh_replacevar(char **envs, char pipe[1024], int c_pos);
void		wsh_escape(char **envs, char pipe[1024]);
void		wsh_stick_redi(t_wsh_tokens *wsh_token, char *string);
void		wsh_fill_redirection(t_wsh_tokens *wsh_token, char redi[][1024], int *c_i);
#endif