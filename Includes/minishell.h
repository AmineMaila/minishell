/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:25:42 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/13 19:28:07 by nazouz           ###   ########.fr       */
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

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h> 
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>

// pipex
typedef struct s_data
{
	char	***env;
	int		*pids;
	int		infd;
	int		id_count;
	int		heredoc;
}				t_data;

typedef struct s_cmd_table
{
	char	**line;
	int		infd;
	int		outfd;
}				t_cmd_table;

typedef struct	s_list_parse
{
	char				*str;
	int					flag;
	struct s_list_parse	*next;
}				t_list_parse;

typedef struct s_minishell
{
	t_cmd_table			*cmd_table;
	char				**cmd_line;
	char				**env;
	char				*input;
	int					cmd_table_size;
	int					pipeinfd;
}	t_minishell;

//	MINISHELL
void			input_lexer(t_minishell *minishell);
void			parse(t_minishell *minishell);
void			command_table(t_minishell *minishell, t_list_parse *lst);
void			minishell_env(t_minishell *minishell, char **env);
char			*get_env(char **env, char *str);

//	LIBFT
char			**ft_split(char const *s, char *charset);
char			**split(char const *s, char *charset);
t_list_parse	*ft_lstnew(char *str);
void			ft_lstadd_back(t_list_parse **lst, char *str);
void			ft_lstdelone(t_list_parse *lst);
void			ft_lstclear(t_list_parse **lst);
int				ft_strcmp(char *s1, char *s2);

//	HELPERS
void			ft_print_cmd_table(t_minishell *minishell);
void			ft_print_matrix(char **matrix);
void			ft_exit(char *cmd, char *str, int ext);
void			flag(t_list_parse **lst);
void			expand_var(t_list_parse **lst, t_list_parse *node, int start);
int				is_operator(char c);
int				is_space(char c);
int				is_quote(char c);
int				get_quote_index(char *str, int i);
int				get_cmd_table_size(t_list_parse *lst);
int				get_line_size(t_list_parse *lst, int pipe_line);
t_list_parse	*get_pipe_line(t_list_parse *lst, int pipe_line);
int				open_redins(t_list_parse *lst, int pipe_line);

// get_next_line
char			*get_next_line(int fd);
int				newline(char *buf);
char			*ft_strcpy(char *s1, char *s2);
char			*ft_strncat(char *dest, const char *src, unsigned int nb);

void			execute(t_cmd_table *table, char ***env, int size);
int				is_cmd(char **token, char **env);
int				here_doc(char *lim);
void			ft_exit(char *cmd, char *str, int ext);
void			free_2d(char ***arr);

char			*alloc_cpy(char *str, char **result, int n);

// built ins
void			ft_add(char ***env, char *to_add);
int				update(char *to_replace, char ***env);
int				len_2d(char **arr);
int				exec_parent(char **line, char ***env);
int				exec_builtin(char **line, char ***env);
void			echo(char **line);
void			environment(char **env);
void			unset(char **line, char ***env);
void			export(char **line, char ***env);
int				cd(char *path, char **env);
int				exit_builtin(char **args);
void			pwd(char **env);


void			print_parse(t_list_parse *lst);
void			print_open_file_descriptors(void);



#endif