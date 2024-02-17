/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:33:14 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/17 21:21:01 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	var_end(char *str, int start)
{
	int	i;

	i = start;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

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

int	env_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	not_expandable(char c)
{
	if (c == '\0' || (c >= 9 && c <= 13)
		|| c == 32 || c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	expansion(t_mini *mini, t_list_parse *curr)
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
		expand_var(mini, curr);
}
