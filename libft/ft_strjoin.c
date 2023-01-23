/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:02:26 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/21 09:33:50 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	s1len;
	size_t	s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	dst = (char *)malloc(s1len + s2len + 1);
	if (dst == 0)
		return (0);
	ft_memcpy(dst, s1, s1len);
	ft_memcpy(dst + s1len, (const char *)s2, s2len);
	dst[s1len + s2len] = '\0';
	return (dst);
}
