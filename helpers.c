/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:06:40 by nazouz            #+#    #+#             */
/*   Updated: 2024/01/31 23:49:30 by nazouz           ###   ########.fr       */
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
		printf("[%s]\n", i, matrix[i]);
		i++;
	}
}
