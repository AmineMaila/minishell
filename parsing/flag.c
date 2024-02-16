/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:21:14 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/16 17:30:46 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	var_start(t_list_parse *curr)
{
	int	i;

	i = 0;
	while (curr->str[i])
	{
		if (curr->str[i] == '$' && curr->str[i + 1]
			&& curr->str[i + 1] != '\"'
			&& curr->str[i + 1] != '\'')
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

char	get_quote(char *str)
{
	int		i;
	char	quote;

	quote = '\0';
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			break ;
		}
		i++;
	}
	return (quote);
}

char	*delquote(char **str, int count)
{
	char	*result;
	char	quote;
	int		len;
	int		j;
	int		i;

	len = ft_strlen(*str) - count;
	result = malloc((len + 1) * sizeof(char));
	quote = get_quote(*str);
	i = 0;
	j = 0;
	while ((*str)[j])
	{
		if ((*str)[j] != quote)
			result[i++] = (*str)[j];
		j++;
	}
	result[i] = '\0';
	free(*str);
	return (result);
}

int	quote_count(t_minishell *minishell, t_list_parse *curr)
{
	char	quote;
	int		expansion;
	int 	i;
	int 	count;

	i = 0;
	count = 0;
	quote = get_quote(curr->str);
	expansion = 0;
	while (curr->str[i])
		if (curr->str[i++] == '$')
			expansion++;
	if (quote != '\'')
		while (expansion--)
			if (!expand_var(minishell, curr))
				break ;
	if (!quote)
		return (0);
	while (curr->str[i])
	{
		if (curr->str[i] == quote)
			count++;
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
			count = quote_count(minishell, curr);
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