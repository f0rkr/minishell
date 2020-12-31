/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:50:56 by mashad            #+#    #+#             */
/*   Updated: 2020/12/31 12:26:55 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list			*node;
	t_list			*tmp;

	node = *lst;
	while (node)
	{
		tmp = node;
		node = node->next;
		if (del)
			del(tmp);
		free(tmp);
	}
	*lst = NULL;
}
