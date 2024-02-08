/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:21:14 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/08 14:29:45 by mmaila           ###   ########.fr       */
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
			free(tmp);
			return (0);
		}
		*token = cmd;
		free(tmp);
	}
	return (1);
}

void	var_start(t_list_parse **lst, t_list_parse *curr)
{
	int	i;

	i = 0;
	while (curr->str[i])
	{
		if (curr->str[i] == '$' && curr->str[i + 1])
		{
			expand_var(lst, curr, i + 1);
			break ;
		}
		i++;
	}
}

void	redirections(t_list_parse *lst, int flag)
{
	if (flag == REDIN)
	{
		if (!lst->str[1])
			lst->flag = REDIN;
		else if (lst->str[1] == '<' && !lst->str[2])
			lst->flag = HEREDOC;
		else
			lst->flag = ERR;
	}
	else
	{
		if (!lst->str[1])
			lst->flag = REDOUT;
		else if (lst->str[1] == '>' && !lst->str[2])
			lst->flag = APPEND;
		else
			lst->flag = ERR;
	}
}

void	flag(t_list_parse **lst, char **env)
{
	t_list_parse	*curr;
	int				is_arg;
	int				cmd[2];

	is_arg = 0;
	cmd[0] = 0; // meaning current cmd line is avaible for a command
	cmd[1] = 1; // meaning the current node can be a command
	curr = *lst;
	while(curr)
	{
		if (*curr->str ==  '|')
			(curr->flag = PIPE, is_arg = 0, cmd[0] = 0, cmd[1] = 1);
		else if (*curr->str ==  '<')
			(redirections(curr, REDIN), is_arg = 0, cmd[1] = 0);
		else if (*curr->str ==  '>')
			(redirections(curr, REDOUT), is_arg = 0, cmd[1] = 0);
		else
		{
			if (*curr->str != '\'')
				var_start(lst, curr);
			if (*curr->str == '\"' || *curr->str == '\'')
				curr->str = ft_strtrim(&curr->str, curr->str[0]);
			if (cmd[0] == 0 && cmd[1] == 1)
				(is_cmd(&curr->str, env), curr->flag = COMMAND, is_arg = 1, cmd[0] = 1);
			else if (is_arg)
				(curr->flag = ARG, cmd[1] = 0);
			else
				(curr->flag = FILEE, is_arg = 1, cmd[1] = 1);
		}
		curr = curr->next;
	}
}