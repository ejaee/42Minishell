/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:26:20 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 10:22:38 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1c;
	const unsigned char	*s2c;
	size_t				idx;

	s1c = (const unsigned char *)s1;
	s2c = (const unsigned char *)s2;
	idx = 0;
	while (idx < n)
	{
		if (*(s1c + idx) != *(s2c + idx))
			return (*(s1c + idx) - *(s2c + idx));
		idx++;
	}
	return (0);
}
