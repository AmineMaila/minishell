/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:15:15 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/23 12:58:46 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	open_out(t_list_parse *out_op, t_list_parse *redout)
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

int	open_in(t_list_parse *in_op, t_list_parse *redin)
{
	int		fd;

	if (!in_op->next->str[0])
		return (print_error(NULL, "ambiguous redirect"), -1);
	fd = open(in_op->next->str, O_RDONLY);
	if (fd == -1)
		return (print_error(in_op->next->str, NULL), -1);
	if (in_op == redin)
		return (fd);
	return (close(fd), -2);
}

void	open_all_fds(t_mini *mini, int pipe)
{
	t_list_parse	*curr;

	curr = get_pipe_line(mini->lst, pipe);
	while (curr && curr->flag != PIPE)
	{
		if (curr->flag == REDIN)
		{
			if (mini->table[pipe].infd > 2)
				close(mini->table[pipe].infd);
			mini->table[pipe].infd = open_in(curr, mini->table[pipe].redin);
		}
		else if (curr->flag == REDOUT || curr->flag == APPEND)
		{
			if (mini->table[pipe].outfd > 2)
				close(mini->table[pipe].outfd);
			mini->table[pipe].outfd = open_out(curr, mini->table[pipe].redout);
		}
		if (mini->table[pipe].infd == -1 || mini->table[pipe].outfd == -1)
		{
			mini->exit_status = 1;
			return ;
		}
		curr = curr->next;
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
