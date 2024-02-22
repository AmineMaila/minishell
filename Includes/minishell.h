/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:25:42 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/22 19:59:19 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define COMMAND 1
# define PIPE 2
# define ARG 3
# define REDIN 4
# define REDOUT 5
# define FILEE 6
# define HEREDOC 7
# define APPEND 8
# define ERR 9
# define ERR2 10
# define LIM 11

# define BUFFER_SIZE 10
# define MSH "\033[1;34mminishell"
# define MSG "\033[2;30m-\033[0m\033[1;36m4.81\033[1;32m × \033[0m"

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <sys/stat.h>

//	FLAGS
typedef struct s_flag
{
	int	is_arg;
	int	cmd_line;
	int	cmd;
}				t_flag;

//	PIPEX
typedef struct s_data
{
	char	***env;
	int		infd;
	int		id_count;
	int		heredoc;
}				t_data;

//	LINKED LIST
typedef struct s_list_parse
{
	char				*str;
	int					flag;
	struct s_list_parse	*next;
}				t_list_parse;

//	COMMAND_TABLE (PIPELINE)
typedef struct s_table
{
	char			**line;
	int				infd;
	int				outfd;
	t_list_parse	*redin;
	t_list_parse	*redout;
}				t_table;

//	MINISHELL
typedef struct s_mini
{
	t_list_parse	*lst;
	t_table			*table;
	char			**cmd_line;
	char			**env;
	char			*input;
	int				sig;
	int				*pids;
	int				table_size;
	int				exit_status;
	int				syntax;
}	t_mini;

//	MINISHELL
void			input_lexer(t_mini *mini);
int				parse(t_mini *mini);
int				command_table(t_mini *mini);
int				mini_env(t_mini *mini, char **env);
char			*get_env(char **env, char *str);

//	FLAG
void			flag(t_mini *mini);
char			*delquote(char **str, int count);
void			redirections(t_list_parse *lst, int flag);
int				quote_count(t_list_parse *curr);

//	EXPANSION
void			expand_var(t_mini *mini, char **str);
int				envvar_count(char *str);
int				var_end(char *str, int start);
int				var_start(char *str);
int				not_expandable(char c);
int				expansion(t_mini *mini, t_list_parse **curr);

//	EXECUTION
int				execute(t_mini *mini);
int				is_cmd(t_mini *mini, char **token, char **env);
int				here_doc(t_mini *mini, t_list_parse *next);
void			free_2d(char ***arr);
void			print_error(char *var, char *msg);
char			*alloc_cpy(char **str, int n);

//	BUILTINS
int				ft_add(char ***env, char *to_add);
int				update(char *to_replace, char ***env);
int				len_2d(char **arr);
int				exec_parent(t_mini *mini, char **line);
int				exec_builtin(t_mini *mini, char **line);
int				echo(char **line);
int				environment(char **env);
int				unset(char **line, char ***env);
int				export(char **line, char ***env);
int				cd(char *path, char ***env);
int				exit_builtin(char **args, long long exit_code);
int				pwd(char **env);

//	SIGNALS
void			sigint_cmd(int signum);
void			signals_handler(void);
void			sig_int(int signum);
void			sig_quit(int signum);

//	LIBFT+
char			**split(char const *s, char *charset);
t_list_parse	*ft_lstnew(char *str);
void			ft_lstadd_back(t_list_parse **lst, char *str);
void			ft_lstdelone(t_list_parse *lst);
void			ft_lstclear(t_list_parse **lst);
int				ft_strcmp(char *s1, char *s2);

//	UTILS
void			ft_exit(t_mini *mini, char *cmd, char *str, int ext);
int				is_operator(char c);
int				is_space(char c);
int				is_quote(char c);
int				get_quote_index(char *str, int i);
int				get_table_size(t_list_parse *lst);
int				get_line_size(t_mini *mini, int pipe_line);
void			closefds(t_mini *mini);
t_list_parse	*get_pipe_line(t_list_parse *lst, int pipe_line);
int				open_redins(t_mini *mini, int pipe_line);
int				open_out(t_list_parse *redout);
int				final_check(t_mini *mini,
					t_list_parse *redin, int heredoc_fd, int pipe_line);
void			set_fds(t_mini *mini);

//	GET_NEXT_LINE
char			*get_next_line(int fd);
int				newline(char *buf);
char			*ft_strcpy(char *s1, char *s2);
char			*ft_strncat(char *dest, const char *src, unsigned int nb);

#endif