/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:42:03 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/16 16:52:23 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	var_end(char *str, int start)
{
	int	i;

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
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*strrem(t_list_parse *node, char *envvar, int start, int len)
{
	char	*result;
	int		resultlen;
	int		j;
	int		i;

	resultlen = (ft_strlen(node->str) - len) + ft_strlen(envvar);
	result = malloc(resultlen + 1);
	if (!result)
		return (free(node->str), NULL);
	j = 0;
	i = 0;
	while (node->str[i])
	{
		if (i == start - 1)
		{
			i += len + 1;
			while (envvar && *envvar)
			{
				result[j++] = *envvar;
				envvar++;
			}
		}
		result[j++] = node->str[i++];
	}
	result[j] = '\0';
	return (free(node->str), result);
}

int	expand_var(t_minishell *minishell, t_list_parse *node)
{
	char	*varname;
	char	*envvar;
	int		start;
	int		end;

	start = var_start(node);
	if (!start)
		return (0);
	end = var_end(node->str, start);
	varname = ft_substr(node->str, start, end - start);
	envvar = get_env(minishell->env, varname);
	free(varname);
	if (!envvar && (end - start + 1) == (int)ft_strlen(node->str))
	{
		delete_node(&minishell->lst, node);
		return (1);
	}
	node->str = strrem(node, envvar, start, end - start);
	if (!node->str)
		cleanup(minishell, errno);
	return (1);
}
