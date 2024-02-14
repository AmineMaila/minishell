/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:15:21 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/14 16:37:13 by nazouz           ###   ########.fr       */
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
	if (!minishell->env)
		ft_exit(NULL, NULL, errno);
	pwd = getcwd(0, 0);
	if (!pwd)
		ft_exit(NULL, NULL, errno);
	minishell->env[0] = ft_strjoin("PWD=", pwd);
	if (!minishell->env[0])
		ft_exit(NULL, NULL, errno);
	free(pwd);
	minishell->env[1] = ft_strdup("SHLVL=1");
	if (!minishell->env[1])
		ft_exit(NULL, NULL, errno);
	minishell->env[2] = ft_strdup("PATH=/bin:/bin:/usr/bin:/usr/ucb:/usr/local/bin");
	if (!minishell->env[2])
		ft_exit(NULL, NULL, errno);
	minishell->env[3] = NULL;
}

int	env_fill(t_minishell *minishell, char **env)
{
	int			i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			minishell->env[i] = ft_strjoin("SHLVL=", ft_itoa(ft_atoi(env[i] + 6) + 1));
			if (!minishell->env[i])
				return (0);
			i++;
		}
		else
		{
			minishell->env[i] = ft_strdup(env[i]);
			if (!minishell->env[i])
				return (0);
			i++;
		}
	}
	minishell->env[i] = NULL;
	return (1);
}

int	minishell_env(t_minishell *minishell, char **env)
{
	int			size;

	if (!env || !env[0])
		return (default_env(minishell), 1);
	size = 0;
	while (env[size])
		size++;
	minishell->env = malloc(sizeof(char *) * (size + 1));
	if (!minishell->env)
		ft_exit(NULL, NULL, errno);
	if (!env_fill(minishell, env))
		ft_exit(NULL, NULL, errno);
	return (1);
}
