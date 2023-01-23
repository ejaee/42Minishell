/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:14:45 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 15:58:07 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newnode;
	t_list	*startnode;

	startnode = ft_lstnew(f(lst->content));
	if (startnode == (void *)0)
		return ((void *)0);
	lst = lst->next;
	while (lst)
	{
		newnode = ft_lstnew(f(lst->content));
		if (newnode == (void *)0)
		{
			ft_lstclear(&startnode, del);
			return ((void *)0);
		}
		ft_lstadd_back(&startnode, newnode);
		lst = lst->next;
	}
	return (startnode);
}
