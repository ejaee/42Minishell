/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:08:34 by ilhna             #+#    #+#             */
/*   Updated: 2023/01/30 14:03:12 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_di(va_list *ap, int fd)
{
	int		len;
	int		num;
	char	*str;

	num = va_arg(*ap, int);
	str = ft_itoa(num);
	ft_putstr_fd(str, fd);
	len = ft_strlen(str);
	free(str);
	str = 0;
	return (len);
}
