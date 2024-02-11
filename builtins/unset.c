/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:48:06 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/11 23:00:56 by mmaila           ###   ########.fr       */
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

void	ft_remove(char ***env, char *to_remove)
{
	char	**result;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	result = malloc(len_2d(*env) * sizeof(char *));
	len = ft_strlen(to_remove);
	while (env[i])
	{
		if (!ft_strncmp(env[i], to_remove, len) && (env[i]) + len == '=')
			i++;
		else
			(*result)[j++] = ft_strdup(env[i++]); // protect
	}
	(*result)[i] = NULL;
	free_2d(env);
	*env = result;
}

void	unset(char **line, char ***env)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if(getenv(line[i]))
			ft_remove(env, line[i]);
		i++;
	}
}