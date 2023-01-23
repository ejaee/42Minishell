/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:07:42 by ilhna             #+#    #+#             */
/*   Updated: 2022/12/30 17:18:58 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char ***outarr_p)
{
	char	**outarr;
	int		idx;

	outarr = *outarr_p;
	idx = 0;
	while (*(outarr + idx))
	{
		free(*(outarr + idx));
		*(outarr + idx) = 0;
		idx++;
	}
	free(*outarr_p);
	*outarr = 0;
}
