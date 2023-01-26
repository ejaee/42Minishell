/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:53:34 by ilhna             #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2023/01/25 15:15:58 by ilhna            ###   ########.fr       */
=======
/*   Updated: 2023/01/26 19:52:00 by choiejae         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "M O N G S H E L L$ "

# include "libft.h"

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_config
{
	t_list	*env_list;
}	t_config;

void	load_config(t_config *config, char **envp);
t_env	*new_env(const char	*env);



void	panic(char *s);


#endif
