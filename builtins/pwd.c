/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:04:41 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/18 18:28:53 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	pwd(char **env)
{
	char	*arr;

	arr = getcwd(0, 0);
	if (!arr)
	{
		arr = get_env(env, "PWD");
		if (!arr)
			return (1);
		arr = ft_strdup(arr);
		if (!arr)
			return (ENOMEM);
	}
	printf("%s\n", arr);
	free(arr);
	return (0);
}
