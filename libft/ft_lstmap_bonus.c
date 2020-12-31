/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:52:27 by mashad            #+#    #+#             */
/*   Updated: 2020/12/31 12:33:27 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list			*rs;
	t_list			*node;

	node = NULL;
	if (!f || !del)
		return (NULL);
	while (lst != NULL)
	{
		if (node == NULL)
		{
			if (!(rs = ft_lstnew(f(lst->type))) && !f(lst->type))
				return (NULL);
			node = rs;
		}
		else
		{
			if (!(node->next = ft_lstnew(f(lst->type))))
				ft_lstclear(&rs, del);
			node = node->next;
		}
		lst = lst->next;
	}
	return (rs);
}
