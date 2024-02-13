/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:40:57 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/13 12:49:42 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

// int	update_pwd(char *path, char **env)
// {
	
// }

int	chdir_relative(char *path, char **env)
{
	char	pwd[PATH_MAX];
	char	*temp;

	(void)env;
	if (!getcwd(pwd, PATH_MAX))
		return (ft_exit(NULL, NULL, 0), -1);
	if ((ft_strlen(pwd) + ft_strlen(path) + 1) >= PATH_MAX)
		return (printf("minishell: cd: path is too long\n"), -1);
	temp = ft_strjoin(pwd, "/"); // malloc protection
	path = ft_strjoin(temp, path); // malloc protection
	free(temp);
	if (chdir(path) != 0)
		return (free(path), ft_exit(path, ": No such file or directory", 0), -1);
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
			return (ft_exit(NULL, NULL, 0), -1);
		return (1);
	}
	else if (path[1]) // if path == "~/some/thing"
	{
		if ((ft_strlen(home) + ft_strlen(path)) >= PATH_MAX)
			return (printf("minishell: cd: path is too long\n"), -1);
		path = ft_strjoin(home, &path[1]); // malloc protection
	}
	if (chdir(path) != 0)
		return (free(path), ft_exit(path, ": No such file or directory", 0), -1);
	return (free(path), 1);
}

int	cd(char *path, char **env)
{
	if (path && (ft_strlen(path) + 1 >= PATH_MAX))
		return (printf("minishell: cd: path is too long\n"), -1);
	if (!path || path[0] == '~')  // if path contains '~'
	{
		chdir_home(path, env);
		// update_pwd(path, env);
		// return (chdir_home(path, env));
	}
	if (path[0] != '/') // if path is relative
		return (chdir_relative(path, env));
	if (chdir(path) != 0) // absolute path
		return (ft_exit(path, ": No such file or directory", 0), -1);
	return (1);
}
