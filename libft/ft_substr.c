/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:33:17 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/21 09:33:56 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	slen;

	slen = ft_strlen(s);
	if (start > slen - 1)
	{
		dst = (char *)malloc(1);
		*dst = '\0';
		if (dst == (void *)0)
			return ((void *)0);
		return (dst);
	}
	if (slen - start < len)
		len = slen - start;
	dst = (char *)malloc(len + 1);
	if (dst == (void *)0)
		return ((void *)0);
	dst = ft_memcpy((void *)dst, (void *)(s + start), len);
	dst[len] = '\0';
	return (dst);
}
