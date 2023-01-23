/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:09:22 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 15:59:57 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	frontidx;
	size_t	backidx;

	frontidx = 0;
	backidx = ft_strlen(s1) - 1;
	while (s1[frontidx] && ft_strchr(set, s1[frontidx]))
		frontidx++;
	while (s1[backidx] && ft_strchr(set, s1[backidx]) && \
			backidx > frontidx)
		backidx--;
	res = ft_substr(s1, frontidx, backidx - frontidx + 1);
	return (res);
}
