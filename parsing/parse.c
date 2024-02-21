/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:05:44 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/21 22:28:30 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	split_line(t_list_parse *lst)
{
	int			nodes;

	nodes = 0;
	while (lst && lst->flag != PIPE)
	{
		if (lst->flag == COMMAND || lst->flag == ARG)
			nodes++;
		lst = lst->next;
	}
}

void	syntax_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd("`", 2);
	if (!str)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(str, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd("\n", 2);
}

int	syntax(t_list_parse *lst)
{
	int			i;

	i = 0;
	if (lst->flag == PIPE)
		return (syntax_error(lst->str), -1);
	while (lst)
	{
		if (lst->flag == ERR2)
			return (ft_putstr_fd("minishell: syntax error: unclosed quote\n",
					2), -1);
		if ((lst->flag == REDIN || lst->flag == REDOUT
				|| lst->flag == HEREDOC || lst->flag == APPEND))
		{
			if (lst->next == NULL)
				return (syntax_error(NULL), -1);
			else if (lst->next->flag == PIPE || lst->next->flag == REDOUT
				|| lst->next->flag == HEREDOC || lst->next->flag == APPEND)
				return (syntax_error(lst->next->str), -1);
		}
		if ((lst->flag == PIPE && lst->next == NULL) || lst->flag == ERR
			|| (lst->flag == PIPE && lst->next->flag == PIPE))
			return (syntax_error(lst->str), -1);
		lst = lst->next;
	}
	return (0);
}

int	parse(t_mini *mini)
{
	int			i;

	if (!mini->cmd_line[0])
		return (1);
	i = 0;
	while (mini->cmd_line[i])
		ft_lstadd_back(&mini->lst, mini->cmd_line[i++]);
	flag(mini);
	if (!mini->lst)
		return (1);
	if (syntax(mini->lst) == -1)
		mini->syntax = 1;
	if (!command_table(mini))
		ft_exit(mini, NULL, NULL, ENOMEM);
	if (mini->syntax)
		return (closefds(mini), mini->syntax = 0, mini->exit_status = 258, 1);
	if (mini->exit_status == 7)
		return (mini->exit_status = 1, 1);
	signal(SIGQUIT, sig_quit);
	execute(mini);
	return (0);
}
