/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:48:02 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/26 11:26:23 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	**lstcp;
	t_list	*dummy_node;

	lstcp = lst;
	if (*lstcp == (void *)0)
		*lstcp = new;
	else
	{
		dummy_node = ft_lstlast(*lstcp);
		dummy_node->prev->next = new;
		new->prev = dummy_node->prev;
		dummy_node->prev = new;
		new->next = dummy_node;
	}
}
