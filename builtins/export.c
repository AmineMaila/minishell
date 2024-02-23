/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:47:56 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/23 17:02:31 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*add_var(char *to_add)
{
	char	*result;
	int		j;
	int		k;

	k = 0;
	j = 0;
	while (to_add[j])
	{
		if (to_add[j] != '+')
			k++;
		j++;
	}
	result = malloc (k + 1);
	if (!result)
		return (NULL);
	j = 0;
	k = 0;
	while (to_add[j])
	{
		if (to_add[j] != '+')
			result[k++] = to_add[j];
		j++;
	}
	result[k] = '\0';
	return (result);
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
	result[i] = add_var(to_add);
	if (!result[i])
		return (free_2d(&result), ENOMEM);
	result[++i] = NULL;
	free_2d(env);
	*env = result;
	return (0);
}

int	ft_increment(char ***env, char *to_increment, int len, int index)
{
	char	*increment;
	char	*result;

	increment = ft_strjoin(((*env)[index] + len + 1), to_increment + len + 2);
	if (!increment)
		return (0);
	result = ft_substr((*env)[index], 0, varlen((*env)[index]) + 1);
	if (!result)
		return (free(increment), 0);
	free((*env)[index]);
	(*env)[index] = ft_strjoin(result, increment);
	(free(increment), free(result));
	if (!(*env)[index])
		return (0);
	return (1);
}

int	update(char *to_replace, char ***env)
{
	int		len;
	int		i;

	len = varlen(to_replace);
	if (!len)
		return (print_error(to_replace, "not a valid identifier"), -1);
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], to_replace, len) && (*env)[i][len] == '=')
		{
			if (!ft_strncmp(to_replace + len, "+=", 2))
			{
				if (!ft_increment(env, to_replace, len, i))
					return (ENOMEM);
				return (0);
			}
			(free((*env)[i]), (*env)[i] = ft_strdup(to_replace));
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
	int			i;
	int			value;
	int			failed;

	i = 1;
	failed = 0;
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
			failed = 1;
		else if (value == ENOMEM)
			return (ENOMEM);
		i++;
	}
	return (failed);
}
