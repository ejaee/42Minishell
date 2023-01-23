/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:18:42 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 11:25:08 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1cp;
	unsigned char	*s2cp;
	size_t			idx;

	s1cp = (unsigned char *)s1;
	s2cp = (unsigned char *)s2;
	idx = 0;
	while (idx < n)
	{
		if (*(s1cp + idx) == 0 || *(s1cp + idx) != *(s2cp + idx))
			return (*(s1cp + idx) - *(s2cp + idx));
		idx++;
	}
	return (0);
}
