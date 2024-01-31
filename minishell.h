/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:25:42 by nazouz            #+#    #+#             */
/*   Updated: 2024/01/31 16:22:00 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h> 
# include <fcntl.h>
# include <signal.h>

typedef struct s_lexer
{
	char	*str;
	int		text;
	int		token;
}	t_lexer;

typedef struct s_minishell
{
	char				*input;
	char				**cmd_line;
	char				**cmd_line_x;
	char				***tok_line;
	char				**parser;
	int					input_red;
	int					output_red;
	struct s_lexer		*lexer;
	int					lexer_size;
}	t_minishell;


//	MINISHELL
void	input_lexer(t_minishell *minishell);

//	LIBFT
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);

//	HELPERS
void	ft_print_matrix(char **matrix);

#endif