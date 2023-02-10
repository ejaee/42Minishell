/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:46:05 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/07 20:49:07 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newnode;

	if (content == (void *)0)
		return ((void *)0);
	newnode = (t_list *)malloc(sizeof(t_list));
	if (newnode == (void *)0)
		return ((void *)0);
	newnode->content = content;
	newnode->next = (void *)0;
	newnode->prev = (void *)0;
	return (newnode);
}
