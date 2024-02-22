/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:15:15 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/22 19:18:25 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	open_outfile(t_list_parse *out_op, t_list_parse *redout)
{
	int		fd;

	fd = -2;
	if (out_op->flag == REDOUT)
	{
		fd = open(out_op->next->str, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			fd = open(out_op->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);		
	}
	else if (out_op->flag == APPEND)
	{
		fd = open(out_op->next->str, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			fd = open(out_op->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (fd == -1)
		return (print_error(out_op->next->str, NULL), -1);
	if (out_op == redout)
		return (fd);
	return (close(fd), -2);
}

int	open_infile(t_list_parse *in_op, t_list_parse *redin)
{
	int		fd;

	fd = open(in_op->next->str, O_RDONLY);
	if (fd == -1)
		return (print_error(in_op->next->str, NULL), -1);
	if (in_op == redin)
		return (fd);
	return (close(fd), -2);
}

void	open_all_fds(t_mini *mini, int pipe_line)
{
	t_list_parse	*current;

	current = get_pipe_line(mini->lst, pipe_line);
	while (current && current->flag != PIPE)
	{
		if (current->flag == REDIN)
			mini->table[pipe_line].infd = open_infile(current, mini->table[pipe_line].redin);
		else if (current->flag == REDOUT || current->flag == APPEND)
			mini->table[pipe_line].outfd = open_outfile(current, mini->table[pipe_line].redout);
		if (mini->table[pipe_line].infd == -1 || mini->table[pipe_line].outfd == -1)
			return ;
		current = current->next;
	}
}

void	set_fds(t_mini *mini)
{
	int			i;

	i = 0;
	while (i < mini->table_size)
	{
		if (!mini->table[i].redin)
		{
			if (i == 0)
				mini->table[i].infd = open("/dev/stdin", O_RDONLY);
			else
				mini->table[i].infd = -42;
		}
		if (!mini->table[i].redout)
		{
			if (i == mini->table_size - 1)
				mini->table[i].outfd = open("/dev/stdout", O_RDWR | O_TRUNC);
			else
				mini->table[i].outfd = -42;
		}
		open_all_fds(mini, i);
		i++;
	}
}
