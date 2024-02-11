/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:02:23 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/11 22:44:29 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	new_size(char **env, char to_replace, char *replace)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	if (to_replace && !replace)
		return (i - 1);
	else if (!to_replace && replace)
		return (i + 1);
	return (i);
}

void	ft_remove(char ***result, char **env, char *to_remove)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(to_remove);
	while (env[i])
	{
		if (!ft_strncmp(env[i], to_remove, len) && (env[i]) + len == '=')
			i++;
		else
			(*result)[j++] = ft_strdup(env[i++]); // protect
	}
	(*result)[i] = NULL;
}

void	ft_add(char ***result, char **env, char *to_add)
{
	int	i;
	int	len;

	i = 0;
	while (env[i])
	{
		(*result)[i] = ft_strdup(env[i]); // protect
		i++;
	}
	(*result)[i++] = ft_strdup(to_add);
	(*result)[i] = NULL;
}

void	ft_replace(char ***result, char **env, char *to_replace, char *replace)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(to_replace);
	while (env[i])
	{
		if (!ft_strncmp(env[i], to_replace, len) && (env[i]) + len == '=')
			(*result)[i] = ft_strdup(replace);
		else
			(*result)[i] = ft_strdup(env[i]);
		i++;
	}
}

void	manipulate_env(char ***env, char *to_replace, char *replace)
{
	char	**result;

	result = malloc((new_size(*env, to_replace, replace) + 1) * sizeof(char *));
	if (to_replace && !replace)
		ft_remove(&result, env, to_replace);
	else if (!to_replace && replace)
		ft_add(&result, env, replace);
	else
		ft_replace(&result, env, to_replace, replace);
	free_2d(env);
	*env = result;
}
