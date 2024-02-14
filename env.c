/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:15:21 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/14 16:15:22 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

char	*get_env(char **env, char *str)
{
	int			i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(str, env[i], ft_strlen(str))
			&& *(env[i] + ft_strlen(str)) == '=')
			return ((env[i] + ft_strlen(str) + 1));
		i++;
	}
	return (NULL);
}

void	default_env(t_minishell *minishell)
{
	char	*pwd;

	minishell->env = malloc(4 * sizeof(char *));
	pwd = getcwd(0, 0);
	minishell->env[0] = ft_strjoin("PWD=", pwd);
	free(pwd);
	minishell->env[1] = ft_strdup("SHLVL=1");
	minishell->env[2] = ft_strdup("PATH=/bin:/bin:/usr/bin:/usr/ucb:/usr/local/bin");
	minishell->env[3] = NULL;
}

void	minishell_env(t_minishell *minishell, char **env)
{
	int			i;
	int			size;

	if (!env || !env[0])
	{
		default_env(minishell);
		return ;
	}
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
