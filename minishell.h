/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:25:42 by nazouz            #+#    #+#             */
/*   Updated: 2024/01/30 12:50:49 by nazouz           ###   ########.fr       */
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

typedef struct s_minishell
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
char	**ft_split(char const *s, char c);

//	HELPERS
void	ft_print_matrix(char **matrix);

#endif