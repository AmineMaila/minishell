/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:06:40 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/04 20:29:32 by mmaila           ###   ########.fr       */
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
	{
		// printf("ss\n");
		printf("{%p}\n", matrix[i]);
		i++;
	}
	printf("[%s]\n", matrix[i]);
}
