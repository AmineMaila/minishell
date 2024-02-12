/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:47:56 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/12 18:07:59 by mmaila           ###   ########.fr       */
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

void	ft_replace(char ***env, char *to_replace)
{
	int		i;
	int		len;

	i = 0;
	while (to_replace[i] != '=')
	{
		if (!to_replace[i])
			return ;
		i++;
	}
	len = i;
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], to_replace, len) && (env[i]) + len == '=')
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(to_replace);
		}
		i++;
	}
}

void	ft_add(char ***env, char *to_add)
{
	char	*result;
	int		i;
	int		len;

	result = malloc((len_2d(*env) + 2) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		result[i] = ft_strdup(env[i]); // protect
		i++;
	}
	result[i++] = ft_strdup(to_add);
	result[i] = NULL;
	free_2d(env);
	*env = result;
}

void	export(char **line, char ***env)
{
	int	i;

	i = 1;
	if (!line[1])
	{
		environment(*env);
		return ;
	}
	while (line[i])
	{
		if(get_env(*env, line[i]))
			ft_replace(env, line[i]);
		else
			ft_add(env, line[i]);
		i++;
	}
}