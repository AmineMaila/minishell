/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:21:14 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/04 19:50:34 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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

int	var_start(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			return (i + 1);
		i++;
	}
	return (-1);
}

void	flag(t_list_parse **lst, char **env)
{
	t_list_parse	*curr;
	int				is_arg;
	int				start;

	is_arg = 0;
	curr = *lst;
	while(curr)
	{
		start = var_start(curr->str);
		if (is_cmd(&curr->str, env))
			(curr->flag = COMMAND, is_arg = 1);
		else if (!ft_strcmp(curr->str, "|"))
			(curr->flag = PIPE, is_arg = 0);
		else if (start != -1)
			(curr->flag = ARG, expand_var(lst, curr, start));
		else if (!ft_strcmp(curr->str, "<"))
			(curr->flag = REDIN, is_arg = 0);
		else if (!ft_strcmp(curr->str, ">"))
			(curr->flag = REDOUT, is_arg = 0);
		else if (is_arg)
			(curr->flag = ARG);
		else
			curr->flag = FILEE;
		curr = curr->next;
	}
}