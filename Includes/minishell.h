/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:25:42 by nazouz            #+#    #+#             */
/*   Updated: 2024/01/30 22:22:10 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

# define COMMAND 1
# define PIPE 2
# define FLAG 3
# define FILEE 4
# define REDIN 5
# define REDOUT 6


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
	char	***tok_line;
	char	**parser;
	int		input_red;
	int		output_red;
}	t_minishell;


//	MINISHELL
void	tokenize_input(t_minishell *minishell);

//	LIBFT
char	**ft_split(char const *s, char *charset);

//	HELPERS
void	ft_print_matrix(char **matrix);
void	ft_exit(char *cmd, char *str, int ext);
void	flag(t_list_parse *lst, char **env);

#endif