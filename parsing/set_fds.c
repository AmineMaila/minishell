/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:15:15 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/22 19:55:06 by nazouz           ###   ########.fr       */
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

void	ft_print_cmd_table(t_mini *mini)
{
	int		i;
	int		j;

	i = 0;
	while (i < mini->table_size)
	{
		printf("\033[1;36m");
		printf("\n\nPIPE_LINE[%d]\t", i);
		printf("\033[0m");
		printf("\033[1;31m");
		if (mini->table[i].infd == -42)
			printf("IN_FD[PIPE]\t");
		else if (mini->table[i].infd == -1337)
			printf("IN_FD[HERE_DOC]\t");
		else
			printf("IN_FD[%d]\t", mini->table[i].infd);
		printf("\033[0m");
		printf("\033[1;32m");
		if (mini->table[i].outfd == -42)
			printf("OUT_FD[PIPE]\t\n");
		else
			printf("OUT_FD[%d]\t\n", mini->table[i].outfd);
		printf("\033[0m");
		j = 0;
		printf("\033[1;34m");
		while (mini->table[i].line[j] != NULL)
		{
			printf("\t\t[%s]\n", mini->table[i].line[j]);
			j++;
		}
		printf("\033[0m");
		i++;
	}
	printf("\n");
}

void	set_fds(t_mini *mini)
{
	int			i;

	i = 0;
	while (i < mini->table_size)
	{
		printf("========> i = %d\n", i);
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
	ft_print_cmd_table(mini);
}
