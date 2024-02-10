/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:15:21 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/09 18:26:37 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*get_env(t_minishell *minishell, char *str)
{
	t_list_parse	*current;

	if (!minishell->env)
		return (NULL);
	current = minishell->env;
	while (current && current->str)
	{
		if (!ft_strncmp(str, current->str, ft_strlen(str))
			&& *(current->str + ft_strlen(str)) == '=')
			return ((current->str + ft_strlen(str) + 1));
		current = current->next;
	}
	return (NULL);
}

void	minishell_env(t_list_parse **lst, char **env)
{
	int			i;
	char		*tmp;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		tmp = ft_strdup(env[i++]);
		// if (!tmp)
			// ft_exit;
		ft_lstadd_back(lst, tmp);
	}
}
