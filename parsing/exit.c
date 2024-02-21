/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:02:40 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/21 12:21:18 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	print_error(char *var)
{
	ft_putstr_fd("minishell: ", 2);
	if (var)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": ", 2);
	}
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

/*
	mini->cmd_line is a 2D array created by split, needs to be freed
	mini->table is an array of struct that contains a 2D array that contains strings from lst
		so no need to free those strings, we only need to free char **
	mini->input doesn't need to be freed, cuz input_lexer already did it
*/

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
	if (ext == 12)
		errno = ENOMEM;
	if (str)
	{
		ft_putstr_fd("minishell: ", 2);
		if (cmd)
			ft_putstr_fd(cmd, 2);
		ft_putendl_fd(str, 2);
	}
	else if (ext)
		print_error(NULL);
	if (mini)
		cleanup(mini, ext);
	if (ext)
		exit(ext);
}
