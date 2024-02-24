/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:02:40 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/23 22:44:32 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	print_error(char *var, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	if (var)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	free_2d(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
}

void	free_table(t_mini *mini)
{
	int			i;

	i = 0;
	if (!mini->table)
		return ;
	while (i < mini->table_size)
	{
		if (mini->table[i].line)
			free(mini->table[i].line);
		i++;
	}
	free(mini->table);
}

void	cleanup(t_mini *mini, int exit_status)
{
	if (mini->table)
	{
		free_table(mini);
		mini->table = NULL;
	}
	if (mini->lst)
		ft_lstclear(&mini->lst);
	if (mini->cmd_line)
	{
		free(mini->cmd_line);
		mini->cmd_line = NULL;
	}
	if (mini->pids)
	{
		free(mini->pids);
		mini->pids = NULL;
	}
	if (exit_status != EXIT_SUCCESS && mini->env)
		free_2d(&mini->env);
}

void	ft_exit(t_mini *mini, char *cmd, char *str, int ext)
{
	struct stat	file;

	if (ext == 12)
		errno = ENOMEM;
	if (ext == 13)
		ext = 126;
	if (stat(cmd, &file) == 0 && S_ISDIR(file.st_mode))
		print_error(cmd, "is a directory");
	else if (str || ext)
		print_error(cmd, str);
	if (mini)
		cleanup(mini, ext);
	if (ext)
		exit(ext);
}
