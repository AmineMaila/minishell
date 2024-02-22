/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:42:03 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/22 20:10:37 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*strrem(char **str, char *envvar, int start, int len)
{
	char	*result;
	int		j;
	int		i;

	result = malloc((ft_strlen(*str) - len - 1) + ft_strlen(envvar) + 1);
	if (!result)
		return (NULL);
	j = 0;
	i = 0;
	while ((*str)[i])
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
		result[j++] = (*str)[i++];
	}
	return (result[j] = '\0', free(*str), result);
}

void	expand_exit(t_mini *mini, char **str, int start)
{
	char	*exitvar;

	exitvar = ft_itoa(mini->exit_status);
	if (!exitvar)
		ft_exit(mini, NULL, NULL, ENOMEM);
	*str = strrem(str, exitvar, start, 1);
	free(exitvar);
	if (!(*str))
		ft_exit(mini, NULL, NULL, ENOMEM);
}

void	expand_var(t_mini *mini, char **str)
{
	char	*varname;
	char	*envvar;
	int		start;
	int		end;

	start = var_start(*str);
	if (!start || not_expandable((*str)[start]))
		return ;
	if ((*str)[start] == '?')
	{
		expand_exit(mini, str, start);
		return ;
	}
	end = var_end(*str, start);
	varname = ft_substr(*str, start, end - start);
	if (!varname)
		ft_exit(mini, NULL, NULL, ENOMEM);
	envvar = get_env(mini->env, varname);
	free(varname);
	*str = strrem(str, envvar, start, end - start);
	if (!(*str))
		ft_exit(mini, NULL, NULL, ENOMEM);
}

void	expansion(t_mini *mini, t_list_parse **curr)
{
	int				count;
	int				i;

	i = 0;
	count = envvar_count((*curr)->str);
	while (count--)
	{
		if ((*curr)->flag != LIM)
			expand_var(mini, &(*curr)->str);
	}
}
