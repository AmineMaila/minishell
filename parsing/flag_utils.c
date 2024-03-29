/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:57:53 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/21 16:51:18 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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
	if (!result)
		return (NULL);
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
	return (free(*str), result);
}

int	quote_count(t_list_parse *curr)
{
	char	quote;
	int		count;
	int		i;

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
	if (count % 2)
		curr->flag = ERR2;
	return (count);
}
