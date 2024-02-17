/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:42:03 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/17 21:30:03 by mmaila           ###   ########.fr       */
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

char	*strrem(t_list_parse *node, char *envvar, int start, int len)
{
	char	*result;
	int		j;
	int		i;

	result = malloc((ft_strlen(node->str) - len - 1) + ft_strlen(envvar) + 1);
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
			continue ;
		}
		result[j++] = node->str[i++];
	}
	return (result[j] = '\0', free(node->str), result);
}

void	expand_exit(t_mini *mini, t_list_parse *node, int start)
{
	char	*exitvar;

	exitvar = ft_itoa(mini->exit_status);
	if (!exitvar)
		ft_exit(mini, NULL, NULL, 12);
	node->str = strrem(node, ft_itoa(mini->exit_status), start, 1);
	if (!node->str)
		ft_exit(mini, NULL, NULL, 12);
}

int	expand_var(t_mini *mini, t_list_parse *node)
{
	char	*varname;
	char	*envvar;
	int		start;
	int		end;

	start = var_start(node);
	if (!start || not_expandable(node->str[start]))
		return (0);
	if (node->str[start] == '?')
		return (expand_exit(mini, node, start), 1);
	end = var_end(node->str, start);
	varname = ft_substr(node->str, start, end - start);
	envvar = get_env(mini->env, varname);
	free(varname);
	if (!envvar && (end - start + 1) == (int)ft_strlen(node->str))
	{
		delete_node(&mini->lst, node);
		return (1);
	}
	node->str = strrem(node, envvar, start, end - start);
	if (!node->str)
		ft_exit(mini, NULL, NULL, 12);
	return (1);
}
