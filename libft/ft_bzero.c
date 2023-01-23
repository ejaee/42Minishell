/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:06:05 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 08:49:19 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	idx;
	char	*scp;

	if (n == 0)
		return ;
	idx = 0;
	scp = (char *)s;
	while (idx < n)
	{
		*(scp + idx) = '\0';
		idx++;
	}
}
