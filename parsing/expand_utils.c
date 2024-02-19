/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 15:33:14 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/19 23:09:07 by mmaila           ###   ########.fr       */
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

int	var_start(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				break ;
		}
		if (str[i] == '$')
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
	if (c == '_' || c == '?')
		return (0);
	else if (!ft_isalpha(c))
		return (1);
	return (0);
}

int	envvar_count(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}
