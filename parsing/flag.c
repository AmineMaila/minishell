/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:21:14 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/16 20:16:53 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	var_start(t_list_parse *curr)
{
	int	i;

	i = 0;
	while (curr->str[i])
	{
		if (curr->str[i] == '\'')
		{
			i++;
			while (curr->str[i] && curr->str[i] != '\'')
				i++;
			if (!curr->str[i])
				break ;
		}
		if (curr->str[i] == '$')
			return (i + 1);
		i++;
	}
	return (0);
}

void	redirections(t_list_parse *lst, int flag)
{
	if (flag == REDIN)
	{
		if (!lst->str[1])
			lst->flag = REDIN;
		else if (lst->str[1] == '<' && !lst->str[2])
			lst->flag = HEREDOC;
		else
			lst->flag = ERR;
	}
	else
	{
		if (!lst->str[1])
			lst->flag = REDOUT;
		else if (lst->str[1] == '>' && !lst->str[2])
			lst->flag = APPEND;
		else
			lst->flag = ERR;
	}
}

char	*delquote(char **str, int count)
{
	char	*result;
	char	quote;
	int		j;
	int		i;

	result = malloc(((ft_strlen(*str) - count) + 1) * sizeof(char));
	i = 0;
	j = 0;
	while ((*str)[j])
	{
		if ((*str)[j] == '\'' || (*str)[j] == '\"')
		{
			quote = (*str)[j++];
			while ((*str)[j] && (*str)[j] != quote)
				result[i++] = (*str)[j++];
			if ((*str)[j] == quote)
				j++;
			continue ;
		}
		result[i++] = (*str)[j++];
	}
	result[i] = '\0';
	free(*str);
	return (result);
}

void	expansion(t_minishell *minishell, t_list_parse *curr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (curr->str[i])
	{
		if (curr->str[i] == '$')
			count++;
		i++;
	}
	while (count--)
		expand_var(minishell, curr);
}

int	quote_count(t_list_parse *curr)
{
	char	quote;
	int 	count;
	int 	i;

	count = 0;
	i = 0;
	while (curr->str[i])
	{
		if (curr->str[i] == '\'' || curr->str[i] == '\"')
		{
			count++;
			quote = curr->str[i++];
			while (curr->str[i] && curr->str[i] != quote)
				i++;
			if (!curr->str[i])
				continue ;
			count++;
		}
		i++;
	}
	return (count);
}

void	flag(t_minishell *minishell)
{
	t_list_parse	*curr;
	int				is_arg;
	int				cmd[2];
	int				count;

	is_arg = 0;
	cmd[0] = 0; // meaning current cmd line is avaible for a command
	cmd[1] = 1; // meaning the current node can be a command
	curr = minishell->lst;
	while(curr)
	{
		if (*curr->str ==  '|')
			(curr->flag = PIPE, is_arg = 0, cmd[0] = 0, cmd[1] = 1);
		else if (*curr->str ==  '<')
		{
			(redirections(curr, REDIN), is_arg = 0, cmd[1] = 0);
			if (curr->flag == HEREDOC && curr->next)
				(curr->next->flag = LIM, cmd[1] = 1);
		}
		else if (*curr->str ==  '>')
			(redirections(curr, REDOUT), is_arg = 0, cmd[1] = 0);
		else
		{
			expansion(minishell, curr);
			count = quote_count(curr);
			if (count)
			{
				if (count % 2)
					curr->flag = ERR2;
				curr->str = delquote(&curr->str, count);
			}
			if (cmd[0] == 0 && cmd[1] == 1 && !curr->flag)
				(curr->flag = COMMAND, is_arg = 1, cmd[0] = 1);
			else if (is_arg && !curr->flag)
				(curr->flag = ARG, cmd[1] = 0);
			else if (!curr->flag)
				(curr->flag = FILEE, is_arg = 1, cmd[1] = 1);
		}
		
		curr = curr->next;
	}
}