/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:56:55 by nazouz            #+#    #+#             */
/*   Updated: 2024/01/30 14:13:52 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	get_mode(t_minishell *minishell)
// {
// 	if (minishell->cmd_line[0][0] == '<' && !minishell->cmd_line[0][1])
// 		minishell->input_red = 1;
// 	else if (ft_strchr(minishell->cmd_line[0], '<'))
// }

void	lexer_search(t_minishell *minishell)
{
	int			i;

	i = 0;
	while (i < minishell->lexer_size)
	{
		if (minishell->lexer[i].str[0] == '\0')
			return ;
		if (ft_strchr(minishell->lexer[i].str, '>')
			|| ft_strchr(minishell->lexer[i].str, '<')
			|| ft_strchr(minishell->lexer[i].str, '|'))
			minishell->lexer->token = 1;
		if (ft_strchr)
		
	}
}

void	create_lexer(t_minishell *minishell)
{
	int		i;
	
	minishell->cmd_line = ft_split(minishell->input, ' ');
	i = 0;
	while (minishell->cmd_line[i])
		i++;
	minishell->lexer_size = i;
	minishell->lexer = malloc(sizeof(t_lexer) * i);
	i = 0;
	while (minishell->cmd_line[i])
	{
		minishell->lexer[i].str = minishell->cmd_line[i];
		minishell->lexer[i].text = 0;
		minishell->lexer[i].token = 0;
		i++;
	}
}

void	input_lexer(t_minishell *minishell)
{
	int		i;

	i = 0;
	while (i < minishell->lexer_size)
	{
		if (ft_strchr(minishell->lexer[i].str, '>')
			|| ft_strchr(minishell->lexer[i].str, '<')
			|| ft_strchr(minishell->lexer[i].str, '|'))
			minishell->lexer->token = 1;
		i++;
	}
}

void	tokenize_input(t_minishell *minishell)
{
	
	
}
