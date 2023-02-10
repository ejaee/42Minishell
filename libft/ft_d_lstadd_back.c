/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_lstadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:48:52 by choiejae          #+#    #+#             */
/*   Updated: 2023/02/09 22:48:56 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_d_lstadd_back(t_list **lst, t_list *new)
{
	t_list	**lstcp;
	t_list	*dummy_node;

	lstcp = lst;
	dummy_node = ft_lstlast(*lstcp);
	dummy_node->prev->next = new;
	new->prev = dummy_node->prev;
	dummy_node->prev = new;
	new->next = dummy_node;
}
