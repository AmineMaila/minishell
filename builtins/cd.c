/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:40:57 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/12 13:28:40 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	chdir_home(t_minishell *minishell, char *dir)
{
	char	*temp;

	if (!dir[1])
	{
		dir = get_env(minishell->env, "HOME");
		if (!dir)
		{
			printf("minishell: cd: HOME not set");
			return ;
		}
	}
	else
	{
		temp = ft_substr(dir, 1, ft_strlen(&dir[1]));
		if (!temp)
			return ;
		dir = ft_strjoin("~", temp);
		if (!dir)
		{
			free(temp);
			return ;
		}
	}
	if (chdir(dir) == -1)
		perror("minishell");
}

void	cd(t_minishell *minishell, char **line)
{
	char	*dir;
	char	*temp;
	char	*home;

	dir = line[0];
	if (!ft_strncmp(dir, "~", 1))
	{
		chdir_home(minishell, dir);
		// update pwd
	}
	else if (chdir(dir) == -1)
	{
		perror("minishell");
		// update pwd
	}
}
