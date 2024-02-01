/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:42:03 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/01 19:30:20 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	expand_var(t_list_parse *node, char **env)
{
	int		i;
	int		var_len;

	i = 0;
	var_len = ft_strlen(node->str);
	while (ft_strncmp(node->str + 1, env[i], var_len - 1))
		i++;
	free(node->str);
	node->str = ft_substr(env[i], var_len, ft_strlen(env[i]) - var_len);
}
