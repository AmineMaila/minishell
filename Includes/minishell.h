/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:25:42 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/01 14:07:51 by nazouz           ###   ########.fr       */
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
char	**ft_split(char const *s, char *charset);

//	HELPERS
void	ft_print_matrix(char **matrix);
void	ft_exit(char *cmd, char *str, int ext);
void	flag(t_list_parse *lst, char **env);

void	print_parse(t_list_parse *lst);

#endif