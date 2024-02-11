/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:37:35 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/11 19:39:40 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	env(t_minishell *minishell)
{
	int			i;

	if (!minishell->env || !minishell->env[0])
		return ;
	i = 0;
	while (minishell->env[i])
		printf("%s\n", minishell->env[i++]);
	return ;
}
