/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:36:28 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 10:59:51 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*bcp;
	size_t			idx;

	bcp = (unsigned char *)b;
	idx = 0;
	while (idx < len)
	{
		*(bcp + idx) = c;
		idx++;
	}
	return (b);
}
