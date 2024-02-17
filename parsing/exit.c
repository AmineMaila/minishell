/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:02:40 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/17 20:12:37 by mmaila           ###   ########.fr       */
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

void	free_cmd_table(t_minishell *minishell)
{
	int			i;

	i = 0;
	if (!minishell->cmd_table)
		return ;
	while (i < minishell->cmd_table_size)
	{
		if (minishell->cmd_table[i].line)
			free(minishell->cmd_table[i++].line);
		i++;
	}
	free(minishell->cmd_table);
}

/*
	minishell->cmd_line is a 2D array created by split, needs to be freed
	minishell->cmd_table is an array of struct that contains a 2D array that contains strings from lst
		so no need to free those strings, we only need to free char **
	minishell->input doesn't need to be freed, cuz input_lexer already did it
*/

void	cleanup(t_minishell *minishell, int exit_status)
{
	if (minishell->cmd_table)
	{
		free_cmd_table(minishell);
		minishell->cmd_table = NULL;
	}
	if (minishell->lst)
		ft_lstclear(&minishell->lst);
	if (minishell->cmd_line)
	{
		free(minishell->cmd_line);
		minishell->cmd_line = NULL;
	}
	if (exit_status != EXIT_SUCCESS)
		free_2d(&minishell->env);
}

void	ft_exit(t_minishell *minishell, char *cmd, char *str, int ext)
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
		perror("minishell");
	if (minishell)
		cleanup(minishell, ext);
	if (ext)
		exit(ext);
}
