/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:53:34 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/07 22:15:39 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Parsed command representation */

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define BACK 5

# define MAXARGS 10

struct	cmd
{
	int	type;
};

struct execcmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
};

struct redircmd
{
	int			type;
	struct cmd	*cmd;
	char		*file;
	char		*efile;
	int			mode;
	int			fd;
};

struct pipecmd
{
	int			type;
	struct cmd	*left;
	struct cmd	*right;
};

struct backcmd
{
	int			type;
	struct cmd	*cmd;
};

/* color */

# define RED	"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[34m"
# define WHITE	"\x1b[0m"
# define BROWN	"\e[38;5;137m"
# define CYAN	"\x1b[36m"
# define RESET	"\x1b[0m"

/* string */

# define PROMPT BROWN"M O N G S H E L L$ "RESET
# define PROMPT_NAME "M O N G S H E L L"

# define ERR_EXIT_MANY_ARGS "exit: too many arguments"
# define ERR_EXIT_NUMERIC "numeric argument required"
# define ERR_CD "No such file or directory"
# define ERR_EXPORT "not a valid identifier"

# define WHITE_SPACE " \t\r\n\v"

/* flag */

# define PERMISSION 1
# define PERMISSION_DENIED 0

# include <fcntl.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/_types/_pid_t.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/param.h>
# include "libft.h"
# include "ft_printf.h"

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_config
{
	t_list	*head;
	t_list	*tail;
}	t_config;

/* builtin_cd.c */
int		builtin_cd(char *buf, t_config *config, int output_flag);

/* builtin_echo.c */
int		builtin_echo(char *const argv[], t_config *config);

/* builtin_env_set.c */
t_list	*get_env_list(t_list *env_list, char *env_key);
int		set_env_list(t_list *env_list, char *env_key, char *new_value);
int		builtin_export(char *buf, t_config *config, int flag);
int		builtin_unset(char *const buf, t_config *config, int flag);

/* builtin_exit.c */
int		builtin_exit(char *const argv[], int flag);

/* builtin_func.c */
int		builtin_pwd(void);
int		builtin_env(char *buf, t_config config, int export_flag);
int		builtin_func(char *buf, char **argv, t_config *config);

/* load_config.c */
void	load_config(t_config *config, char **envp);

/* main.c */
int skip_space_check_toks(char **out_ps, char *str_end, char *toks);

/* new_env */
t_env	*new_env(const char	*env);

/* parse_quote */
int	parse_quote(char *buf);

/* signals.c */
void	set_son_signal();
void	sig_ctrl_c(int signal);
void	set_signal();

/* utils.c */
void	free_split(char **str);
void	ft_del(void *content);
void	panic(char *s);

#endif
