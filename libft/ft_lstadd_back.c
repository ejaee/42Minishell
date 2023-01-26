/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:48:02 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/26 15:11:26 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	**lstcp;
	t_list	*lastnode;

	lstcp = lst;
	if (*lstcp == (void *)0)
		*lstcp = new;
	else
	{
		lastnode = ft_lstlast(*lstcp);
		lastnode->next = new;
	}
}