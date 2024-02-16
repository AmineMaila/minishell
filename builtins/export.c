/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:47:56 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/16 16:14:31 by nazouz           ###   ########.fr       */
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

void	ft_add(char ***env, char *to_add)
{
	char	**result;
	int		i;

	result = malloc((len_2d(*env) + 2) * sizeof(char *));
	i = 0;
	while ((*env)[i])
	{
		result[i] = ft_strdup((*env)[i]); // protect
		i++;
	}
	result[i++] = ft_strdup(to_add);
	result[i] = NULL;
	free_2d(env);
	*env = result;
}

int	update(char *to_replace, char ***env)
{
	int	len;
	int	i;

	len = varlen(to_replace);
	if (!len)
		return (ft_exit(to_replace, ": not a valid identifier", 0), 1);
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], to_replace, len) && (*env)[i][len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(to_replace); // if failed means malloc error should cleanup and exit
			if (!(*env)[i])
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export(char **line, char ***env)
{
	int	i;

	i = 1;
	if (!line[1])
		return (environment(*env));
	while (line[i])
	{
		if (!update(line[i], env)) // multiple cases either malloc, on didn't found to_replace
			ft_add(env, line[i]);
		i++;
	}
}
