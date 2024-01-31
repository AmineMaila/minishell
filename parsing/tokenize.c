/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:56:55 by nazouz            #+#    #+#             */
/*   Updated: 2024/01/30 15:40:22 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	get_mode(t_minishell *minishell)
{
	if (minishell->cmd_line[0][0] == '<')
	{
		
	}
}

void	tokenize_input(t_minishell *minishell)
{
	int		i;
	
	minishell->cmd_line = ft_split(minishell->input, ' ');
	i = 0;
	while (minishell->cmd_line[i])
	{
		get_mode(minishell);
	}
}
