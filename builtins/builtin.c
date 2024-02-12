/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:19:58 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/12 17:30:10 by mmaila           ###   ########.fr       */
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

int	exec_builtin(char **line, char ***env)
{
	char	*lower;

	lower = to_lower(line[0]);
	if (!ft_strcmp("echo", lower))
		return(echo(line), 1);
	else if(!ft_strcmp("cd", line[0]))
		return(cd(line[0], *env), 1);
	else if(!ft_strcmp("pwd", lower))
		return(pwd(), 1);
	// else if(!ft_strcmp("export", line[0]))
	// 	return(export(), 1);
	else if(!ft_strcmp("unset", line[0]))
		return(unset(line, env), 1);
	else if(!ft_strcmp("env", lower))
		return(environment(*env), 1);
	// else if(!ft_strcmp("exit", line[0]))
	// 	return(exit(), 1);
	else
		return (0);
}