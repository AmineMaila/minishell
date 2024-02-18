/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:48:06 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/18 18:30:31 by nazouz           ###   ########.fr       */
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
		return (ENOMEM);
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], to_remove, ft_strlen(to_remove))
				&& *(((*env)[i]) + ft_strlen(to_remove)) == '=')
			i++;
		else
		{
			result[j] = ft_strdup((*env)[i++]);
			if (!result[j++])
				return (free_2d(&result), ENOMEM);
		}
	}
	result[j] = NULL;
	free_2d(env);
	*env = result;
	return (0);
}

int	unset(char **line, char ***env)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (get_env(*env, line[i]))
		{
			if (ft_remove(env, line[i]) == ENOMEM)
				return (ENOMEM);
		}
		i++;
	}
	return (0);
}
