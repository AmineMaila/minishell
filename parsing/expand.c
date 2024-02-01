/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:42:03 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/02 00:24:15 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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

char	*to_upper(char *str)
{
	char	*upper;
	int		i;

	upper = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!upper)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			upper[i] = str[i] - 32;
		else
			upper[i] = str[i];
		i++;
	}
	upper[i] = '\0';
	return (upper);
}

void	expand_var(t_list_parse **lst, t_list_parse *node, char **env)
{
	char	*upper;
	int		i;
	int		var_len;

	i = 0;
	upper = to_upper(node->str);
	// if (!upper)
	// 	exit
	while (env[i])
	{
		if (!ft_strncmp(node->str + 1, env[i], env_len(env[i])) 
			|| !ft_strncmp(upper + 1, env[i], env_len(env[i])))
			break;
		i++;
	}
	free(upper);
	if (!env[i])
	{
		delete_node(lst, node);
		return ;
	}
	free(node->str);
	var_len = env_len(env[i]);
	node->str = ft_substr(env[i], var_len + 1, ft_strlen(env[i]) - var_len);
}
