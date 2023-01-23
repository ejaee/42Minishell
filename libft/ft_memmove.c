/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:26:41 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 11:03:43 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	movedata(unsigned char **dstcp, unsigned char **srccp, size_t len);

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dstcp;
	unsigned char	*srccp;

	if (dst == (void *)0 && src == (void *)0)
		return ((void *)0);
	dstcp = (unsigned char *)dst;
	srccp = (unsigned char *)src;
	movedata(&dstcp, &srccp, len);
	return (dst);
}

static void	movedata(unsigned char **dstcp, unsigned char **srccp, size_t len)
{
	size_t	idx;

	idx = 0;
	if (*dstcp <= *srccp)
	{
		while (idx < len)
		{
			*(*dstcp + idx) = *(*srccp + idx);
			idx++;
		}
	}
	else
	{
		*dstcp += len - 1;
		*srccp += len - 1;
		while (idx < len)
		{
			*(*dstcp - idx) = *(*srccp - idx);
			idx++;
		}
	}
}
