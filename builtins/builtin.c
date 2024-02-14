/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:19:58 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/13 19:38:16 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int		len_2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

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

int	exec_parent(char **line, char ***env)
{
	if (!ft_strcmp("unset", line[0]))
		return (unset(line, env), 1);
	else if (!ft_strcmp("export", line[0]))
		return (export(line, env), 1);
	else if(!ft_strcmp("cd", line[0]))
		return(cd(line[1], *env), 1);
	return (0);
}

int	exec_builtin(char **line, char ***env)
{
	char	*lower;

	lower = to_lower(line[0]);
	if (!ft_strcmp("echo", lower))
		return(echo(line), 1);
	else if(!ft_strcmp("pwd", lower))
		return(pwd(*env), 1);
	else if(!ft_strcmp("env", lower))
		return(environment(*env), 1);
	else if(!ft_strcmp("exit", line[0]))
	{
		printf("exit_buitin\n");
		return(exit_builtin(line), 1);
	}
	return (0);
}