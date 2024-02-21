/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:44:17 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/21 12:53:17 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*get_path(t_mini *mini, char *cmd, char **env)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	while (env[i] && ft_strncmp("PATH", env[i], 4))
		i++;
	if (!env[i])
		return (NULL);
	path = ft_split(env[i] + 5, ":");
	if (!path)
		ft_exit(mini, NULL, NULL, errno);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i++], cmd);
		if (!tmp)
			return (free_2d(&path), ft_exit(mini, NULL, NULL, errno), NULL);
		if (!access(tmp, F_OK))
			return (free_2d(&path), tmp);
		free(tmp);
	}
	free_2d(&path);
	return (NULL);
}

int	is_cmd(t_mini *mini, char **token, char **env)
{
	char	*tmp;
	char	*cmd;

	if (access(*token, F_OK | X_OK))
	{
		tmp = ft_strjoin("/", *token);
		if (!tmp)
			ft_exit(mini, NULL, NULL, ENOMEM);
		cmd = get_path(mini, tmp, env);
		if (!cmd)
		{
			free(tmp);
			return (0);
		}
		*token = cmd;
		free(tmp);
	}
	return (1);
}
