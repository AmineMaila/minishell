/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:21:14 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/01 19:43:46 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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

void	flag(t_list_parse *lst, char **env)
{
	t_list_parse	*curr;
	t_list_parse	*prev;
	int				is_arg;
	int				is_text;

	is_arg = 0;
	is_text = 0;
	curr = lst;
	prev = lst;
	while(curr)
	{
		if (is_cmd(&curr->str, env))
			(curr->flag = COMMAND, is_arg = 1);
		else if (!ft_strcmp(curr->str, "|"))
			(curr->flag = PIPE, is_arg = 0);
		else if (!ft_strcmp(curr->str, "\""))
		{
			(curr->flag = DQUOTE, is_arg = 0);
			if (!is_text)
				is_text = 1;
			else
				is_text = 0;
		}
		else if (!ft_strcmp(curr->str, "<"))
			(curr->flag = REDIN, is_arg = 0);
		else if (curr->str[0] == '$')
			(curr->flag = VAR, is_arg = 0, expand_var(&lst, curr->str, env));
		else if (!ft_strcmp(curr->str, ">"))
			(curr->flag = REDOUT, is_arg = 0);
		else if (is_arg)
			(curr->flag = ARG);
		else if (is_text)
			(curr->flag = TEXT);
		else
			curr->flag = FILEE;
		prev = curr;
		curr = curr->next;
	}
}