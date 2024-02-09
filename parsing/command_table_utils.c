/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:35:24 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/08 19:22:31 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_list_parse	*get_pipe_line(t_list_parse *lst, int pipe_line)
{
	t_list_parse	*current;
	int				i;

	i = 0;
	current = lst;
	if (pipe_line == 0)
		return (current);
	while (current && i != pipe_line)
	{
		if (current->flag == PIPE)
			i++;
		current = current->next;
	}
	return (current);
}

int	get_cmd_table_size(t_list_parse *lst)
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
