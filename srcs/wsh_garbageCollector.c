/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsh_garbageCollector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:50:06 by mashad            #+#    #+#             */
/*   Updated: 2021/01/05 15:50:08 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     wsh_garbageCollector(t_wsh_list *wsh_list)
{
    if (wsh_list->string != NULL)
    {
        free(wsh_list->string);
        wsh_list->string = NULL;
    }
    if (wsh_list->ast_parsed != NULL)
    {
        free(wsh_list->ast_parsed);
        wsh_list->ast_parsed = NULL;
    }
    if (wsh_list->garbage_flag == ERROR)
    {
        wsh_list->garbage_flag = INIT;
        return (ERROR);
    }
    //ft_free();
    return (EXIT);
}