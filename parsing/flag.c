/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:21:14 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/19 22:41:00 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	operator(t_flag *flags, t_list_parse *curr)
{
	if (*curr->str == '|')
	{
		curr->flag = PIPE;
		flags->is_arg = 0;
		flags->cmd_line = 0;
		flags->cmd = 1;
	}
	else if (*curr->str == '<')
	{
		redirections(curr, REDIN);
		flags->is_arg = 0;
		flags->cmd = 0;
		if (curr->flag == HEREDOC && curr->next)
		{
			curr->next->flag = LIM;
			flags->cmd = 1;
			flags->is_arg = 1;
		}
	}
	else if (*curr->str == '>')
	{
		redirections(curr, REDOUT);
		flags->is_arg = 0;
		flags->cmd = 0;
	}
}

void	words(t_list_parse *curr, t_flag *flags)
{
	if (flags->cmd_line == 0 && flags->cmd == 1)
	{
		curr->flag = COMMAND;
		flags->is_arg = 1;
		flags->cmd_line = 1;
	}
	else if (flags->is_arg)
	{
		curr->flag = ARG;
		flags->cmd = 0;
	}
	else
	{
		curr->flag = FILEE;
		flags->is_arg = 1;
		flags->cmd = 1;
	}
}

void	flag(t_mini *mini)
{
	t_list_parse	*curr;
	t_flag			flags;
	int				count;

	flags.is_arg = 0;
	flags.cmd_line = 0;
	flags.cmd = 1;
	curr = mini->lst;
	while (curr)
	{
		operator(&flags, curr);
		if (!expansion(mini, &curr))
			continue ;
		count = quote_count(curr);
		if (count)
		{
			curr->str = delquote(&curr->str, count);
			if (!curr->str)
				ft_exit(mini, NULL, NULL, ENOMEM);
		}
		if (!curr->flag)
			words(curr, &flags);
		curr = curr->next;
	}
}
