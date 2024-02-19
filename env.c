/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:15:21 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/19 14:44:24 by mmaila           ###   ########.fr       */
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

void	default_env(t_mini *mini)
{
	char	*pwd;

	mini->env = malloc(4 * sizeof(char *));
	if (!mini->env)
		ft_exit(mini, NULL, NULL, ENOMEM);
	pwd = getcwd(0, 0);
	if (!pwd)
		ft_exit(mini, NULL, NULL, ENOMEM);
	mini->env[0] = ft_strjoin("PWD=", pwd);
	if (!mini->env[0])
		ft_exit(mini, NULL, NULL, ENOMEM);
	free(pwd);
	mini->env[1] = ft_strdup("SHLVL=1");
	if (!mini->env[1])
		ft_exit(mini, NULL, NULL, ENOMEM);
	mini->env[2]
		= ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin");
	if (!mini->env[2])
		ft_exit(mini, NULL, NULL, ENOMEM);
	mini->env[3] = NULL;
}

int	env_fill(t_mini *mini, char **env)
{
	char	*lvl;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			lvl = ft_itoa(ft_atoi(env[i] + 6) + 1);
			if (!lvl)
				return (0);
			mini->env[i] = ft_strjoin("SHLVL=", lvl);
			free(lvl);
			if (!mini->env[i])
				return (0);
			i++;
		}
		else
		{
			mini->env[i] = ft_strdup(env[i]);
			if (!mini->env[i])
				return (0);
			i++;
		}
	}
	mini->env[i] = NULL;
	return (1);
}

int	mini_env(t_mini *mini, char **env)
{
	if (!env || !env[0])
		return (default_env(mini), 1);
	mini->env = malloc(sizeof(char *) * (len_2d(env) + 1));
	if (!mini->env)
		ft_exit(mini, NULL, NULL, ENOMEM);
	if (!env_fill(mini, env))
		ft_exit(mini, NULL, NULL, ENOMEM);
	return (1);
}
