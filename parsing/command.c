/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:21:14 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/01 19:30:57 by nazouz           ###   ########.fr       */
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
	int				is_arg;
	int				is_text;

	is_arg = 0;
	is_text = 0;
	tmp = lst;
	while (tmp)
	{
		if (is_cmd(&tmp->str, env))
			(tmp->flag = COMMAND, is_arg = 1);
		else if (!ft_strcmp(tmp->str, "|"))
			(tmp->flag = PIPE, is_arg = 0);
		else if (!ft_strcmp(tmp->str, "\""))
		{
			(tmp->flag = DQUOTE, is_arg = 0);
			if (!is_text)
				is_text = 1;
			else
				is_text = 0;
		}
		else if (!ft_strcmp(tmp->str, "<"))
			(tmp->flag = REDIN, is_arg = 0);
		else if (tmp->str[0] == '$')
			(tmp->flag = VAR, is_arg = 0, expand_var(tmp, env));
		else if (!ft_strcmp(tmp->str, ">"))
			(tmp->flag = REDOUT, is_arg = 0);
		else if (is_arg)
			(tmp->flag = ARG);
		else if (is_text)
			(tmp->flag = TEXT);
		else
			tmp->flag = FILEE;
		tmp = tmp->next;
	}
}