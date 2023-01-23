/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:47:30 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 15:58:57 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dstcp;
	unsigned char	*srccp;
	size_t			idx;

	if (dst == (void *)0 && src == (void *)0)
		return ((void *)0);
	dstcp = (unsigned char *)dst;
	srccp = (unsigned char *)src;
	idx = 0;
	while (idx < n)
	{
		*(dstcp + idx) = *(srccp + idx);
		idx++;
	}
	return (dst);
}
