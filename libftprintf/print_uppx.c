/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uppx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:42:30 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/30 14:11:40 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_uppx(va_list *ap, int fd)
{
	char			*hex;
	int				len;
	unsigned int	num;
	char			str[10];

	num = va_arg(*ap, unsigned int);
	if (num == 0)
	{
		if (ft_putchar_fd_cstm('0', fd) == PF_ERROR)
			return (PF_ERROR);
		return (1);
	}
	hex = "0123456789ABCDEF";
	ft_memset(str, 'g', 10);
	len = 0;
	while (num > 0)
	{
		str[10 - len - 1] = hex[num % 16];
		num /= 16;
		len++;
	}
	if (putarr(str, 10, fd) == PF_ERROR)
		return (PF_ERROR);
	return (len);
}
