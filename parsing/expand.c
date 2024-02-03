/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:42:03 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/03 18:38:53 by mmaila           ###   ########.fr       */
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

char	strrem(t_list_parse *node, char *envvar, int len)
{
	char	*result;
	int		resultlen;
	int		i;
	int		j;

	resultlen = (ft_strlen(node->str) - len) + ft_strlen(envvar);
	result = malloc(resultlen + 1);
	j = 0;
	while (*node->str)
	{
		if (*node->str == '$')
		{
			node->str += len;
			while (*envvar)
			{
				result[j] = *envvar;
				j++;
				envvar++;
			}
		}
		result[j++] = *node->str;
		node->str++;
	}
	result[j] = '\0';
	return (free(node->str), result);
}

void	expand_var(t_list_parse **lst, t_list_parse *node, char **env, int start)
{
	char	*var;
	char	*envvar;
	int		end;
	int		i;

	i = 0;
	end = var_end(node->str, start);
	var = ft_substr(node->str, start, end - start);
	envvar = getenv(var);
	free(var);
	if (!envvar)
	{
		delete_node(lst, node);
		return ;
	}
	node->str = strrem(node, envvar, end - start);
}
