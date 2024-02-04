/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:25:42 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/04 19:14:37 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

# define COMMAND 1
# define PIPE 2
# define ARG 3
# define REDIN 4
# define REDOUT 5
# define FILEE 6
# define DQUOTE 7
# define TEXT 8
# define VAR 9
# define SQUOTE 10


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

typedef struct	s_list_parse
{
	char				*str;
	int					flag;
	struct s_list_parse	*next;
}				t_list_parse;

typedef struct	s_minishell
{
	char	*input;
	char	**cmd_line;
	int		input_red;
	int		output_red;
}	t_minishell;


//	MINISHELL
void			input_lexer(t_minishell *minishell);
t_list_parse	*parse(char **str, char **env);

//	LIBFT
char			**ft_split(char const *s, char *charset);
t_list_parse	*ft_lstnew(char *str);
void			ft_lstadd_back(t_list_parse **lst, char *str);
void			ft_lstdelone(t_list_parse *lst);
int				ft_strcmp(char *s1, char *s2);

//	HELPERS
void	ft_print_matrix(char **matrix);
void	ft_exit(char *cmd, char *str, int ext);
void	flag(t_list_parse **lst, char **env);
void	expand_var(t_list_parse **lst, t_list_parse *node, int start);
int		is_operator(char c);
int		is_space(char c);
void	free_2d(char ***arr);
char	*alloc_cpy(char *str, char **result, int n);

void	print_parse(t_list_parse *lst);

#endif