/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:09:16 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/21 09:36:54 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	slen;

	slen = ft_strlen(s1);
	dst = (char *)malloc(slen + 1);
	if (dst == (void *)0)
		return ((void *)0);
	ft_memcpy((void *)dst, (void *)s1, slen);
	dst[slen] = '\0';
	return (dst);
}
