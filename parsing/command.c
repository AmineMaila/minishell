/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:21:14 by mmaila            #+#    #+#             */
/*   Updated: 2024/01/30 22:23:00 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "../libft/libft.h"

void	free_2d(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	path = ft_split(env[i] + 5, ":");
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i++], cmd);
		if (!tmp)
			return (free_2d(&path), NULL);
		if (!access(tmp, F_OK | X_OK))
			return (free_2d(&path), tmp);
		free(tmp);
	}
	free_2d(&path);
	//ft_exit(cmd + 1, ": command not found", 1);
	return (NULL);
}

int	is_cmd(char **token, char **env)
{
	char	*tmp;
	char	*cmd;

	if (access(*token, F_OK | X_OK))
	{
		tmp = ft_strjoin("/", *token);
		if (!tmp)
			ft_exit(NULL, NULL, errno);
		cmd = get_path(tmp, env);
		if (!cmd)
		{
			return (0);
		}
		*token = cmd;
		free(tmp);
	}
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (s1[i] - s2[i]);
}

void	flag(t_list_parse *lst, char **env)
{
	t_list_parse	*tmp;

	tmp = lst;
	while(tmp)
	{
		if (is_cmd(&tmp->str, env))
			tmp->flag = COMMAND;
		else if (!ft_strncmp(tmp->str, "-", 1))
			tmp->flag = FLAG;
		else if (!ft_strcmp(tmp->str, "|"))
			tmp->flag = PIPE;
		else if (!ft_strcmp(tmp->str, "<"))
			tmp->flag = REDIN;
		else if (!ft_strcmp(tmp->str, ">"))
			tmp->flag = REDOUT;
		else
			tmp->flag = FILEE;
		tmp = tmp->next;
	}
}