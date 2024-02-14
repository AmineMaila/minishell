/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:04:41 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/13 19:21:11 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	pwd(char **env)
{
	char	*arr;

	arr = getcwd(0, 0);
	if (!arr)
		arr = ft_strdup(get_env(env, "PWD"));
	printf("%s\n", arr);
	free(arr);
}
