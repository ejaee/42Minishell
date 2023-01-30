/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:04:02 by ilhna             #+#    #+#             */
/*   Updated: 2022/10/04 17:54:59 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_nlen_out_sign(int n, int *sign);

char	*ft_itoa(int n)
{
	size_t	nlen;
	int		sign;
	char	*dst;
	char	*dststart;

	nlen = get_nlen_out_sign(n, &sign);
	dst = (char *)malloc(nlen + 1);
	if (dst == (void *)0)
		return ((void *)0);
	dststart = dst;
	dst[nlen] = '\0';
	if (n == 0)
	{
		dst[0] = '0';
		return (dststart);
	}
	while (n != 0)
	{
		dst[nlen - 1] = (char)(sign * (n % 10) + '0');
		n /= 10;
		nlen--;
	}
	if (sign < 0)
		dst[0] = '-';
	return (dststart);
}

static size_t	get_nlen_out_sign(int n, int *sign)
{
	size_t	nlen;

	nlen = 0;
	*sign = 1;
	if (n == -2147483648)
	{
		*sign = -1;
		return (11);
	}
	else if (n == 0)
		return (1);
	if (n < 0)
	{
		*sign = -1;
		nlen++;
		n *= -1;
	}
	while (n > 0)
	{
		nlen++;
		n /= 10;
	}
	return (nlen);
}
