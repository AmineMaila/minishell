/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:21:14 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/06 18:29:44 by mmaila           ###   ########.fr       */
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

int	flag_operator(t_list_parse *lst)
{
	t_list_parse	*curr;

	curr = lst;
	if (*curr->str ==  '|')
		return (curr->flag = PIPE, 1);
	else if (*curr->str ==  '<')
		return (curr->flag = REDIN, 1);
	else if (*curr->str ==  '>')
		return (curr->flag = REDOUT, 1);
	return (0);
}

void	flag(t_list_parse **lst, char **env)
{
	t_list_parse	*curr;
	int				is_arg;
	int				cmd[2];
	int				start;

	is_arg = 0;
	cmd[0] = 0;
	cmd[1] = 1;
	curr = *lst;
	while(curr)
	{
		if (flag_operator(*lst))
			(is_arg = 0, cmd[1] = 0);
		start = var_start(curr->str);
		if (start != -1 && *curr->str != '\'')
			expand_var(lst, curr, start);
		if (*curr->str == '\"' || *curr->str == '\'')
			curr->str = ft_strtrim(&curr->str, curr->str[0]);
		if (cmd[0] == 0 && cmd[1] == 1 && is_cmd(&curr->str, env))
			(curr->flag = COMMAND, is_arg = 1, cmd[0] = 1);
		else if (is_arg)
			(curr->flag = ARG, cmd[1] = 0);
		else
			(curr->flag = FILEE, is_arg = 1, cmd[1] = 1);
		curr = curr->next;
	}
}