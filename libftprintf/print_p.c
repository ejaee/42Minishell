/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:24:45 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/30 14:10:32 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_p(va_list *ap, int fd)
{
	char			*hex;
	int				len;
	unsigned long	ul_addr;
	char			hex_addr[ADDR_LEN];

	ul_addr = va_arg(*ap, unsigned long);
	if (ul_addr == 0)
	{
		ft_putstr_fd("0x0", fd);
		return (3);
	}
	hex = "0123456789abcdef";
	ft_memset(hex_addr, 'g', ADDR_LEN);
	len = 0;
	while (ul_addr > 0)
	{
		hex_addr[ADDR_LEN - len - 1] = hex[ul_addr % 16];
		ul_addr /= 16;
		len++;
	}
	ft_putstr_fd("0x", fd);
	if (putarr(hex_addr, ADDR_LEN, fd) == PF_ERROR)
		return (PF_ERROR);
	return (len + 2);
}
