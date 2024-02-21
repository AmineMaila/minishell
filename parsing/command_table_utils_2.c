/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:39:09 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/21 12:39:36 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	get_table_size(t_list_parse *lst)
{
	int				pipe_lines;
	t_list_parse	*current;

	pipe_lines = 1;
	current = lst;
	while (current)
	{
		if (current->flag == PIPE)
			pipe_lines++;
		current = current->next;
	}
	return (pipe_lines);
}

int	get_line_size(t_list_parse *lst, int pipe_line)
{
	t_list_parse	*current;
	int				i;
	int				size;

	i = 0;
	current = get_pipe_line(lst, pipe_line);
	size = 0;
	while (current && current->flag != PIPE)
	{
		if (current->flag == COMMAND || current->flag == ARG)
			size++;
		current = current->next;
	}
	return (size);
}
