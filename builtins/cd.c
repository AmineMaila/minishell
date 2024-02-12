/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:40:57 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/12 19:59:02 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	chdir_relative(char *path, char **env)
{
	char	pwd[PATH_MAX];
	char	*temp;

	(void)env;
	if (!getcwd(pwd, PATH_MAX))
		return (perror("minishell: cd"), -1);
	if ((ft_strlen(pwd) + ft_strlen(path) + 1) >= PATH_MAX)
		return (printf("minishell: cd: path is too long\n"), -1);
	temp = ft_strjoin(pwd, "/"); // malloc protection
	path = ft_strjoin(temp, path); // malloc protection
	free(temp);
	if (chdir(path) != 0)
		return (free(path), perror("minishell: cd"), -1);
	return (free(path), 1);
}

int	chdir_home(char *path, char **env)
{
	char	*home;
	
	home = get_env(env, "HOME");
	if (!home)
		return (printf("minishell: cd: HOME is not set\n"), -1);
	if (!path || !path[1]) // if path contains only '~'
	{
		if (chdir(home) != 0)
			return (perror("minishell: cd"), -1);
		return (1);
	}
	else if (path[1]) // if path == "~/some/thing"
	{
		if ((ft_strlen(home) + ft_strlen(path)) >= PATH_MAX)
			return (printf("minishell: cd: path is too long\n"), -1);
		path = ft_strjoin(home, &path[1]); // malloc protection
	}
	if (chdir(path) != 0)
		return (free(path), perror("minishell: cd"), -1);
	return (free(path), 1);
}

int	cd(char *path, char **env)
{
	if (path && (ft_strlen(path) + 1 >= PATH_MAX))
		return (printf("minishell: cd: path is too long\n"), -1);
	if (!path || path[0] == '~') // if path contains '~'
		return (chdir_home(path, env));
	if (path[0] != '/') // if path is relative
		return (chdir_relative(path, env));
	if (chdir(path) != 0)
		return (perror("minishell: cd"), -1);
	return (1);
}
