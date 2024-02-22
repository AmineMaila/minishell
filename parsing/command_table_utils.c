/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:35:24 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/22 12:26:32 by nazouz           ###   ########.fr       */
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

int	open_redins(t_mini *mini, int pipe_line)
{
	t_list_parse	*current;
	int				infd;

	infd = -42;
	current = get_pipe_line(mini->lst, pipe_line);
	while (current && current->flag != PIPE)
	{
		if (current->flag == REDIN)
		{
			close(infd);
			infd = open(current->next->str, O_RDONLY);
			if (infd == -1)
			{
				mini->exit_status = 1;
				print_error(current->next->str, NULL);
				return (-1);
			}
		}
		current = current->next;
	}
	return (infd);
}

int	open_out(t_list_parse *redout)
{
	int			outfd;
	char		*outfile;

	if (!redout->next)
		return (print_error(NULL, "ambiguous redirect"), -1);
	outfile = redout->next->str;
	if (redout->flag == REDOUT)
	{
		outfd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (outfd == -1)
			outfd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfd == -1)
			print_error(outfile, NULL);
		return (outfd);
	}
	else
	{
		outfd = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (outfd == -1)
			outfd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfd == -1)
			print_error(outfile, NULL);
		return (outfd);
	}
}

int	final_check(t_mini *mini, t_list_parse *redin, int heredoc_fd, int pipe_l)
{
	if (!redin)
	{
		if (pipe_l == 0)
			return (open("/dev/stdin", O_RDONLY));
		return (-42);
	}
	if (!redin->next)
		return (print_error(NULL, "ambiguous redirect"), -1);
	if (redin->flag == HEREDOC)
	{
		if (open_redins(mini, pipe_l) == -1)
			return (-1);
		return (heredoc_fd);
	}
	return (close(heredoc_fd), open_redins(mini, pipe_l));
}
