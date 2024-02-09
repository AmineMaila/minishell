/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:59:56 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/09 23:05:56 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	get_outfd(t_minishell *minishell, t_list_parse *lst, int pipe_line)
{
	t_list_parse	*current;
	t_list_parse	*redout;
	char			*outfile;

	redout = NULL;
	current = get_pipe_line(lst, pipe_line);
	while (current && current->flag != PIPE)
	{
		if (current->flag == REDOUT || current->flag == APPEND)
			redout = current;
		current = current->next;
	}
	if (!redout)
	{
		if (pipe_line == minishell->cmd_table_size - 1)
			return (open("/dev/stdout", O_RDONLY));
		return (-42);
	}
	outfile = redout->next->str;
	if (redout->flag == REDOUT)
		return (open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644));
	else // if (redout->flag == APPEND)
		return (open(outfile, O_RDWR | O_CREAT | O_APPEND, 0644));
}

int	get_infd(t_list_parse *lst, int pipe_line)
{
	t_list_parse	*current;
	t_list_parse	*redin;
	char			*infile;
	int				fd;

	redin = NULL;
	current = get_pipe_line(lst, pipe_line);
	while (current && current->flag != PIPE)
	{
		if (current->flag == REDIN || current->flag == HEREDOC)
			redin = current;
		current = current->next;
	}
	if (!redin)
	{
		if (pipe_line == 0)
			return (open("/dev/stdin", O_RDONLY));
		return (-42);
	}
	infile = redin->next->str;
	if (redin->flag == REDIN)
		fd = open(infile, O_RDONLY);
	else // if (redin->flag == HEREDOC)
		return (here_doc(redin->next->str));
	if (fd == -1)
		ft_exit(infile, ": no such file or directory", 0);
	return (fd);
}

void	fill_fds(t_minishell *minishell, t_list_parse *lst, int pipe_line)
{
	minishell->cmd_table[pipe_line].infd = get_infd(lst, pipe_line);
	minishell->cmd_table[pipe_line].outfd = get_outfd(minishell, lst, pipe_line);
	// if (minishell->cmd_table[pipe_line].outfd == -1)
	// 	ft_exit(argv[1], ": no such file or directory", 0);
}

void	fill_line(t_minishell *minishell, t_list_parse *lst, int pipe_line)
{
	int				line_size;
	t_list_parse	*current;
	int				i;

	line_size = get_line_size(lst, pipe_line);
	minishell->cmd_table[pipe_line].line
		= malloc(sizeof(char *) * (line_size + 1));
	if (!minishell->cmd_table[pipe_line].line)
		return ; // needs to be fixed
	current = get_pipe_line(lst, pipe_line);
	i = 0;
	while (i < line_size)
	{
		if (current->flag == COMMAND || current->flag == ARG)
			minishell->cmd_table[pipe_line].line[i++] = current->str;
		current = current->next;
	}
	minishell->cmd_table[pipe_line].line[i] = NULL;
}

void	command_table(t_minishell *minishell, t_list_parse *lst)
{
	int				i;

	minishell->cmd_table_size = get_cmd_table_size(lst);
	minishell->cmd_table = malloc(sizeof(t_cmd_table) * minishell->cmd_table_size);
	if (!minishell->cmd_table)
		return ; // needs to be fixed
	i = 0;
	while (i < minishell->cmd_table_size)
	{
		fill_line(minishell, lst, i);
		fill_fds(minishell, lst, i);
		i++;
	}
}
