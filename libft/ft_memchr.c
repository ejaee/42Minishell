/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:44:40 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 17:59:46 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*sc;
	size_t		idx;

	sc = (const char *)s;
	idx = 0;
	while (idx < n)
	{
		if ((unsigned char)c == *(unsigned char *)(sc + idx))
			return ((void *)(sc + idx));
		idx++;
	}
	return (0);
}
