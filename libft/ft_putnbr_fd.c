/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:48:46 by ilhna             #+#    #+#             */
/*   Updated: 2022/07/20 15:59:06 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	ft_putdigit_fd(int n, int fd);
static void	ft_recur_putnbr_fd(int nb, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	int		min;

	min = -2147483648;
	if (n == min)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	ft_recur_putnbr_fd(n, fd);
}

static void	ft_recur_putnbr_fd(int nb, int fd)
{
	if (nb > 9)
		ft_recur_putnbr_fd(nb / 10, fd);
	ft_putdigit_fd(nb % 10, fd);
}

static void	ft_putdigit_fd(int n, int fd)
{
	char	ch;

	ch = n + '0';
	write(fd, &ch, 1);
}
