/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:40:57 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/16 17:42:14 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

// char	*get_oldpwd(char **env)
// {
// 	char	*oldpwd;

// 	oldpwd = getcwd(0, 0);
// 	if (!oldpwd)
// 		oldpwd = ft_strdup(get_env(env, "PWD"));
// 	if (!oldpwd)
// 		return (NULL);
// 	return (oldpwd);
// }

int	update_oldpwd(char **oldpwd, char ***env)
{
	char	*var;

	if (!(*oldpwd))
		return (0);
	var = ft_strjoin("OLDPWD=", *oldpwd);
	free(*oldpwd);
	if (!update(var, env))
		if (!ft_add(env, var))
			return (free(var), 0);
	return (free(var), 1);
}

int	update_pwd(char *path, char ***env)
{
	char	*pwd;
	char	*temp;
	char	*var;

	pwd = getcwd(0, 0);
	if (!pwd)
	{
		temp = ft_strjoin(get_env(*env, "PWD"), "/");
		if (!temp)
			return (0);
		pwd = ft_strjoin(temp, path);
		if (!pwd)
			return (free(temp), 0);
		free(temp);
	}
	var = ft_strjoin("PWD=", pwd);
	if (!var)
		return (free(pwd), 0);
	free(pwd);
	if (!update(var, env))
		return (free(var), 0);
	return (free(var), 1);
}

int	chdir_relative(char *path, char *oldpwd, char ***env)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories\n", 2);
		pwd = ft_strdup(get_env(*env, "PWD"));
		if (!pwd)
			return (1);
		// update_oldpwd(oldpwd, env);
		// update_pwd(path, env);
		// return (update_oldpwd(oldpwd, env), update_pwd(path, env), -1);
	}
	if ((ft_strlen(pwd) + ft_strlen(path) + 1) >= PATH_MAX)
		return (printf("minishell: cd: path is too long\n"), 1);
	if (chdir(path) != 0)
	{
		update_oldpwd(oldpwd, env);
		update_pwd(path, env);
		return (ft_exit(path, ": No such file or directory", 0), 1);
	}
	return (update_pwd(path, env), update_oldpwd(oldpwd, env), 0);
}

int	cd(char *path, char ***env)
{
	char	*oldpwd;

	oldpwd = getcwd(0, 0);
	// if (!oldpwd)
	// 	oldpwd = ft_strdup(get_env(*env, "PWD"));
	// oldpwd = get_oldpwd(*env);
	if (path && (ft_strlen(path) + 1 >= PATH_MAX))
		return (printf("minishell: cd: path is too long\n"), 1);
	if (path[0] != '/') // if path is relative
		return (chdir_relative(path, oldpwd, env));
	if (chdir(path) != 0) // absolute path
		return (ft_exit(path, ": No such file or directory", 0), 1);
	if (!update_pwd(path, env) || !update_oldpwd(oldpwd, env))
		return (1);
	return (0);
}
