/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:40:57 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/14 16:55:32 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	update_oldpwd(char *oldpwd, char ***env)
{
	char	*var;

	var = ft_strjoin("OLDPWD=", oldpwd);
	// free(oldpwd);
	if (!update(var, env))
		ft_add(env, var);
	// free(var);
	return (1);
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
		pwd = ft_strjoin(temp, path);
		// free(temp);
	}
	var = ft_strjoin("PWD=", pwd);
	// free(pwd);
	update(var, env);
	// free(var);
	return (1);
}

int	chdir_relative(char *path, char *oldpwd, char ***env)
{
	char	*pwd;
	// char	*temp;

	pwd = getcwd(0, 0);
	if (!pwd)
	{
		printf("cd: error retrieving current directory: getcwd: cannot access parent directories\n");
		pwd = ft_strdup(get_env(*env, "PWD"));
		// update_oldpwd(oldpwd, env);
		// update_pwd(path, env);
		// return (update_oldpwd(oldpwd, env), update_pwd(path, env), -1);
	}
	if ((ft_strlen(pwd) + ft_strlen(path) + 1) >= PATH_MAX)
		return (printf("minishell: cd: path is too long\n"), -1);
	if (chdir(path) != 0)
	{
		printf("chdir relative failed\n");
		update_oldpwd(oldpwd, env);
		update_pwd(path, env);
		return (ft_exit(path, ": No such file or directory", 0), -1);
	}
	return (update_pwd(path, env), update_oldpwd(oldpwd, env), 1);
}

int	cd(char *path, char ***env)
{
	char	*oldpwd;

	oldpwd = getcwd(0, 0);
	if (!oldpwd)
		oldpwd = ft_strdup(get_env(*env, "PWD"));
	if (path && (ft_strlen(path) + 1 >= PATH_MAX))
		return (printf("minishell: cd: path is too long\n"), -1);
	if (path[0] != '/') // if path is relative
		return (chdir_relative(path, oldpwd, env));
	printf("full path = %s\n", path);
	if (chdir(path) != 0) // absolute path
		return (ft_exit(path, ": No such file or directory", 0), -1);
	update_pwd(path, env);
	update_oldpwd(oldpwd, env);
	return (1);
}
