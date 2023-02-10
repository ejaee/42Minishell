/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilhna <ilhna@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:53:34 by ilhna             #+#    #+#             */
/*   Updated: 2023/02/10 15:17:25 by ilhna            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

/* Parsed command representation */
# define EXEC 1
# define REDIR 2
# define PIPE 3

# define MAXARGS 10

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
# define PROMPT "M O N G S H E L L$ "
# define PROMPT_NAME "M O N G S H E L L"

# define ERR_EXIT_MANY_ARGS "exit: too many arguments"
# define ERR_EXIT_NUMERIC "numeric argument required"
# define ERR_CD "No such file or directory"
# define ERR_CMD "command not found"
# define ERR_EXPORT "not a valid identifier"

# define WHITE_SPACE " \t\r\n\v"
# define SYMBOLS "<|>&()"

/* flag */
# define PERMISSION 1
# define PERMISSION_DENIED 0

typedef struct s_cmd
{
	int	type;
}				t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}				t_execcmd;

typedef struct s_redircmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
}				t_redircmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}				t_pipecmd;

typedef struct s_env
{
	char	*key;
	char	*value;
}				t_env;

typedef struct s_config
{
	t_list	*head;
	t_list	*tail;
	char	quote_list[MAXARGS];
}				t_config;

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
int		builtin_env(char *buf, t_config config, int export_flag);
int		builtin_func(char *buf, char **argv, t_config *config);

/* load_config.c */
void	load_config(t_config *config, char **envp);

/* main.c */
int		skip_space_check_toks(char **out_ps, char *str_end, char *toks);

/* new_env */
t_env	*new_env(const char	*env);

/* generate)cmd */
t_cmd	*init_execcmd(void);
t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);

/* parse_cmd */
t_cmd	*parse_cmd(char *str);

/* parse_quote */
int		parse_quote(char *buf);

/* runcmd */
void	runcmd(t_cmd *cmd, t_config config);

/* show_shell_logo */
void	show_shell_logo(void);

/* signals.c */
void	set_son_signal(void);
void	set_signal(void);

/* utils.c */
void	free_split(char **str);
void	ft_del(void *content);
void	panic(char *s);
int		skip_space_check_toks(char **out_ps, char *str_end, char *toks);

/* check_buf */
int		check_buf(char **buf, t_config *config);

/* nulterminate.c */
t_cmd	*nulterminate(t_cmd *cmd);

/* get_token.c */
int		get_token(char **out_str_ptr, char *str_end, \
	char **out_q, char **out_eq);

char	**get_envp(t_list *config_head);

#endif
