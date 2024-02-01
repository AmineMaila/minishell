/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:56:55 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/01 19:29:58 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_operator(char c)
{
	if (c == '<'
		|| c == '>'
		|| c == '|'
		|| c == 34
		|| c == 39)
		return (1);
	return (0);
}

char	*insert_spaces(char *str, int n)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (n + 1));
	while (str[i])
	{
		while (is_operator(str[i]))
		{
			result[j++] = str[i];
			result[j++] = ' ';
			i++;
		}
		while (!is_operator(str[i]) && str[i])
		{
			result[j++] = str[i];
			i++;
		}
		result[j++] = ' ';
	}
	result[j] = '\0';
	free(str);
	return (result);
}

void	input_lexer(t_minishell *minishell)
{
	int		i;
	int		op_count;
	int		ch_count;

	i = 0;
	op_count = 0;
	ch_count = 0;
	while (minishell->input[i])
	{
		if (is_operator(minishell->input[i]))
			op_count++;
		else
			ch_count++;
		i++;
	}
	minishell->input
		= insert_spaces(minishell->input, (op_count * 2) + ch_count);
	minishell->cmd_line = ft_split(minishell->input, " ");
}
