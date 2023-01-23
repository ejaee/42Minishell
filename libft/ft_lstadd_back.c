/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:48:02 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 15:56:18 by ilhna            ###   ########.fr       */
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
