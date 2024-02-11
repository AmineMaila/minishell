/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:15:21 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/11 20:08:25 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*get_env(t_minishell *minishell, char *str)
{
	int			i;

	if (!minishell->env)
		return (NULL);
	while (minishell->env[i])
	{
		if (!ft_strncmp(str, minishell->env[i], ft_strlen(str))
			&& *(minishell->env[i] + ft_strlen(str)) == '=')
			return ((minishell->env[i] + ft_strlen(str) + 1));
		i++;
	}
	return (NULL);
}

void	minishell_env(t_minishell *minishell, char **env)
{
	int			i;
	int			size;

	if (!env || !env[0])
		return ;
	size = 0;
	while (env[size])
		size++;
	minishell->env = malloc(sizeof(char *) * (size + 1));
	if (!minishell->env)
		return ;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			minishell->env[i] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(env[i] + 6) + 1)); // malloc protection
			i++;
		}
		else
		{
			minishell->env[i] = ft_strdup(env[i]);
			i++;
		}
	}
	minishell->env[i] = NULL;
}
