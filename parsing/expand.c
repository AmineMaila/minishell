/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:42:03 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/01 19:43:57 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_list_parse	*find_node(t_list_parse	**lst, char *str)
{
	t_list_parse	*prev;
	
	prev = *lst;
	if (!ft_strcmp(prev->str, str))
	{
		*lst = (*lst)->next;
		return (prev);
	}
	while (prev->next)
	{
		if (!ft_strcmp(prev->next->str, str))
			return (prev);
		prev = prev->next;
	}
	return (NULL);
}

void	expand_var(t_list_parse **lst, char *str, char **env)
{
	t_list_parse	*curr;
	t_list_parse	*prev;
	int				i;
	int				var_len;

	i = 0;
	prev = find_node(lst, str);
	curr = prev->next;
	var_len = ft_strlen(curr->str);
	while (env[i] && ft_strncmp(curr->str + 1, env[i], var_len - 1))
		i++;
	if (!env[i])
	{
		prev->next = curr->next;
		ft_lstdelone(curr);
		return ;
	}
	free(curr->str);
	curr->str = ft_substr(env[i], var_len, ft_strlen(env[i]) - var_len);
}
