/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:22:33 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/21 09:33:36 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	**lstcp;
	t_list	*tmpnode;

	lstcp = lst;
	while (*lstcp)
	{
		tmpnode = *lstcp;
		*lstcp = (*lstcp)->next;
		ft_lstdelone(tmpnode, del);
	}
}
