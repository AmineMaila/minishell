/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:19:58 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/11 19:09:33 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*to_lower(char *str)
{
	char	*result;
	int		i;

	result = malloc((ft_strlen(str) + 1) * sizeof(char));
	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			result[i] = str[i] + 32;
		else
			result[i] = str[i];
		i++;
	}
	return (result);
}

int	exec_builtin(char **line)
{
	char	*lower;

	lower = to_lower(line[0]);
	if (!ft_strcmp("echo", lower))
		return(echo(line), 1);
	// else if(!ft_strcmp("cd", lower))
	// 	return(cd(), 1);
	else if(!ft_strcmp("pwd", lower))
		return(pwd(), 1);
	// else if(!ft_strcmp("export", lower))
	// 	return(export(), 1);
	// else if(!ft_strcmp("unset", lower))
	// 	return(unset(), 1);
	// else if(!ft_strcmp("env", lower))
	// 	return(env(), 1);
	// else if(!ft_strcmp("exit", lower))
	// 	return(exit(), 1);
	else
		return (0);
}