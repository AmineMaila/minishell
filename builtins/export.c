/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:47:56 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/22 12:46:15 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	varlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '=')
			return (len);
		if (str[len] != '_' && !ft_isalpha(str[len]))
			return (0);
		len++;
	}
	return (0);
}

int	ft_add(char ***env, char *to_add)
{
	char	**result;
	int		i;

	result = malloc((len_2d(*env) + 2) * sizeof(char *));
	if (!result)
		return (ENOMEM);
	i = 0;
	while ((*env)[i])
	{
		result[i] = ft_strdup((*env)[i]);
		if (!result[i])
			return (free_2d(&result), ENOMEM);
		i++;
	}
	result[i] = ft_strdup(to_add);
	if (!result[i])
		return (free_2d(&result), ENOMEM);
	result[++i] = NULL;
	free_2d(env);
	*env = result;
	return (0);
}

int	update(char *to_replace, char ***env)
{
	int	len;
	int	i;

	len = varlen(to_replace);
	if (!len)
		return (print_error(to_replace, "not a valid identifier"), -1);
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], to_replace, len) && (*env)[i][len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(to_replace);
			if (!(*env)[i])
				return (ENOMEM);
			return (0);
		}
		i++;
	}
	return (1);
}

int	export(char **line, char ***env)
{
	int	i;
	int	value;

	i = 1;
	if (!line[1])
		return (environment(*env));
	while (line[i])
	{
		value = update(line[i], env);
		if (value == 1)
		{
			if (ft_add(env, line[i]) == ENOMEM)
				return (ENOMEM);
		}
		else if (value == -1)
			return (1);
		else if (value == ENOMEM)
			return (ENOMEM);
		i++;
	}
	return (0);
}
