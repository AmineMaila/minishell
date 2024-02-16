/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 19:37:35 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/16 17:28:47 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	environment(char **env)
{
	int			i;

	if (!env || !env[0])
		return (1);
	i = 0;
	while (env[i])
	{
		if (printf("%s\n", env[i++]) == -1)
			return (1);
	}
	return (0);
}
