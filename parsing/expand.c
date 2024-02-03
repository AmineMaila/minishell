/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:42:03 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/03 16:40:55 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	var_end(char *str, int start)
{
	int			i;

	i = start;
	while (ft_isalnum(str[i]))
		i++;
	return (i);
}

void	delete_node(t_list_parse **lst, t_list_parse *node)
{
	t_list_parse	*prev;
	t_list_parse	*tmp;
	
	prev = *lst;
	if (!ft_strcmp(prev->str, node->str))
	{
		ft_lstdelone(prev);
		*lst = (*lst)->next;
		return ;
	}
	while (prev->next)
	{
		if (!ft_strcmp(prev->next->str, node->str))
		{
			tmp = prev->next->next;
			ft_lstdelone(prev->next);
			prev->next = tmp;
			return ;
		}
		prev = prev->next;
	}
}

int	env_len(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	expand_var(t_list_parse **lst, t_list_parse *node, char **env, int start)
{
	int		var_len;
	int		i;

	i = 0;
	
	while (env[i] && ft_strncmp(node->str + 1, env[i], env_len(env[i])))
		i++;
	if (!env[i])
	{
		delete_node(lst, node);
		return ;
	}
	free(node->str);
	var_len = env_len(env[i]);
	node->str = ft_substr(env[i], var_len + 1, ft_strlen(env[i]) - var_len);
}
