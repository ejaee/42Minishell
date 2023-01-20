/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:40:17 by choiejae          #+#    #+#             */
/*   Updated: 2023/01/18 21:36:36 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>



typedef	struct s_cmd
{
    char *exec_file_path;

    char	**argv;
    char	**env;

    char	*input_buffer;
	char 	*output_buffer;

    struct s_cmd	*next;
}   t_cmd;

#endif