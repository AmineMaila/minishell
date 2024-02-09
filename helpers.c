/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:06:40 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/08 20:29:57 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	leaks(void)
{
	system ("leaks minishell");
}

void	ft_print_matrix(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i])
		printf("[%s]\n", matrix[i++]);
}

void	ft_print_cmd_table(t_minishell *minishell)
{
	int		i;
	int		j;

	i = 0;
	while (i < minishell->cmd_table_size)
	{
		printf("\033[1;36m");
		printf("\n\nPIPE_LINE[%d]\t", i);
		printf("\033[0m");
		printf("\033[1;31m");
		if (minishell->cmd_table[i].infd == -42)
			printf("IN_FD[PIPE]\t");
		else if (minishell->cmd_table[i].infd == -1337)
			printf("IN_FD[HERE_DOC]\t");
		else
			printf("IN_FD[%d]\t", minishell->cmd_table[i].infd);
		printf("\033[0m");
		printf("\033[1;32m");
		if (minishell->cmd_table[i].outfd == -42)
			printf("OUT_FD[PIPE]\t\n");
		else
			printf("OUT_FD[%d]\t\n", minishell->cmd_table[i].outfd);
		printf("\033[0m");
		j = 0;
		printf("\033[1;34m");
		while (minishell->cmd_table[i].line[j] != NULL)
		{
			printf("\t\t[%s]\n", minishell->cmd_table[i].line[j]);
			j++;
		}
		printf("\033[0m");
		i++;
	}
	printf("\n");
}
