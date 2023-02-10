/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:50:03 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/10 13:50:26 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	get_token(char **out_str_ptr, char *str_end, char **out_q, char **out_eq)
{
	char	*str;
	int		ret;

	str = *out_str_ptr;
	while (str < str_end && ft_strchr(WHITE_SPACE, *str))
		str++;
	if (out_q)
		*out_q = str;
	ret = set_token(&str, str_end);
	if (out_eq)
		*out_eq = str;
	while (str < str_end && ft_strchr(WHITE_SPACE, *str))
		str++;
	*out_str_ptr = str;
	return (ret);
}
