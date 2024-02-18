/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:48:06 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/18 16:41:42 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	ft_remove(char ***env, char *to_remove)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(len_2d(*env) * sizeof(char *));
	if (!result)
		return (0);
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], to_remove, ft_strlen(to_remove))
				&& *(((*env)[i]) + ft_strlen(to_remove)) == '=')
			i++;
		else
		{
			result[j] = ft_strdup((*env)[i++]);
			if (!result[j++])
				return (free_2d(&result), 0);
		}
	}
	result[j] = NULL;
	free_2d(env);
	*env = result;
	return (1);
}

int	unset(char **line, char ***env)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (get_env(*env, line[i]))
		{
			if (!ft_remove(env, line[i])) // if failed means malloc error
				return (errno); // should cleanup and exit
		}
		i++;
	}
	return (0);
}
