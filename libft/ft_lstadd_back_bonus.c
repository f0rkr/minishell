/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mashad <mashad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:50:15 by mashad            #+#    #+#             */
/*   Updated: 2019/10/19 12:50:07 by mashad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list			*node;

	node = *alst;
	if (!node)
		*alst = new;
	else
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
}
