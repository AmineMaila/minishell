/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:40:57 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/18 18:53:55 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	update_oldpwd(char *oldpwd, char ***env)
{
	int		value;
	char	*var;

	if (!oldpwd)
		return (0);
	var = ft_strjoin("OLDPWD=", oldpwd);
	if (!var)
		return (ENOMEM);
	value = update(var, env);
	if (value == 1)
	{
		if (ft_add(env, var) == ENOMEM)
			return (free(var), ENOMEM);
	}
	else if (value == ENOMEM)
		return (ENOMEM);
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
			return (ENOMEM);
		pwd = ft_strjoin(temp, path);
		if (!pwd)
			return (free(temp), ENOMEM);
		free(temp);
	}
	var = ft_strjoin("PWD=", pwd);
	if (!var)
		return (free(pwd), ENOMEM);
	free(pwd);
	if (update(var, env) == ENOMEM)
		return (free(var), ENOMEM);
	return (free(var), 1);
}

int	chdir_relative(char *path, char **oldpwd, char ***env)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!pwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories\n", 2);
		pwd = get_env(*env, "PWD");
		if (!pwd)
			return (1);
		pwd = ft_strdup(pwd);
		if (!pwd)
			return (free(*oldpwd), ENOMEM);
		// update_oldpwd(oldpwd, env);
		// update_pwd(path, env);
		// return (update_oldpwd(oldpwd, env), update_pwd(path, env), -1);
	}
	if ((ft_strlen(pwd) + ft_strlen(path) + 1) >= PATH_MAX)
		return (free(pwd), ft_putstr_fd("minishell: cd: path is too long\n", 2), 1);
	if (chdir(path) != 0)
		return (free(pwd), free(*oldpwd), ft_exit(NULL, path, ": No such file or directory", 0), 1);
	if (update_pwd(path, env) == ENOMEM || update_oldpwd(*oldpwd, env) == ENOMEM)
		return (free(pwd), free(*oldpwd), ENOMEM);
	return (free(pwd), free(*oldpwd), 0);
}

int	cd(char *path, char ***env)
{
	char	*oldpwd;

	if (!path)
		return (0); // go to HOME
	oldpwd = getcwd(0, 0);
	if (!oldpwd)
	{
		oldpwd = get_env(*env, "PWD");
		if (!oldpwd)
			return (1);
		oldpwd = ft_strdup(oldpwd);
		if (!oldpwd)
			return (ENOMEM);
	}
	if (path && (ft_strlen(path) + 1 >= PATH_MAX))
		return (free(oldpwd), ft_putstr_fd("minishell: cd: path is too long\n", 2), 1);
	if (path[0] != '/') // if path is relative
		return (chdir_relative(path, &oldpwd, env));
	if (chdir(path) != 0) // absolute path
		return (free(oldpwd), ft_exit(NULL, path, ": No such file or directory", 0), 1);
	if (!update_pwd(path, env) || !update_oldpwd(oldpwd, env))
		return (free(oldpwd), 1);
	return (free(oldpwd), 0);
}
