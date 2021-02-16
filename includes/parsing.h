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

extern int		wsh_readSquotes(char *str, const char *string, int *counter);
extern int		wsh_readDquotes(char *str, const char *string, int *counter);
extern int		wsh_scan_commands(char *str, const char *string, int pipe);
extern int		is_and(const char *str, int p, int q_flag, int pipe);
#endif