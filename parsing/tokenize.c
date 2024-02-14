/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:56:55 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/14 16:46:56 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	shift_insert(char *result, int src, int dst, int flag)
{
	ft_memmove(&(result[dst]), &(result[src]), ft_strlen(&(result[src])) + 1);
	if (flag == -1)
		result[src] = ' ';
	if (flag == 1)
		result[dst] = ' ';
}

char	*insert_spaces(char *str, int n)
{
	char	*result;
	int		i;

	result = alloc_cpy(str, &result, n);
	i = 0;
	while (result[i])
	{
		if (is_quote(result[i]))
			i = get_quote_index(result, ++i);
		if (is_operator(result[i]))
		{
			if (i > 0 && !is_space(result[i - 1]))
				(shift_insert(result, i, i + 1, -1));
			if (result[i] != '|')
				while (result[i + 1] == '>' || result[i + 1] == '<')
					i++;
			if (!is_space(result[i + 1]) && result[i + 1] != '\0')
				(shift_insert(result, i, i + 1, 1));
		}
		i++;
	}
	return (free(str), result);
}

int	count_needed_spaces(char *str)
{
	int		i;
	int		was_space;
	int		count;

	i = -1;
	count = 0;
	was_space = 0;
	while (str[++i])
	{
		if (is_quote(str[i]))
			i = get_quote_index(str, ++i);
		if (is_operator(str[i]))
		{
			if (i > 0 && !is_space(str[i - 1]) && was_space == 0)
				count++;
			if (str[i] != '|')
				while (str[i + 1] == '>' || str[i + 1] == '<')
					i++;
			if (!is_space(str[i + 1]) && str[i + 1] != '\0')
				(count++, was_space = 1);
		}
		else
			was_space = 0;
	}
	return (count);
}

void	input_lexer(t_minishell *minishell)
{
	int		i;
	int		spaces_count;

	i = 0;
	spaces_count = count_needed_spaces(minishell->input);
	if (spaces_count == 0)
	{
		minishell->cmd_line = split(minishell->input, " \t");
		if (!minishell->cmd_line)
			ft_exit(NULL, NULL, errno);
		return ;
	}
	minishell->input
		= insert_spaces(minishell->input, spaces_count);
	minishell->cmd_line = split(minishell->input, " \t");
}
