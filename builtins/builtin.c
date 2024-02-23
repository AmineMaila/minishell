/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:19:58 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/23 16:58:36 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	varlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '=')
			return (len);
		if (str[len] == '+' && str[len + 1] == '=')
			return (len);
		if (str[len] != '_' && !ft_isalpha(str[len]))
			return (0);
		len++;
	}
	return (0);
}

int	len_2d(char **arr)
{
	int	i;

	if (!arr || !*arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*to_lower(char *str)
{
	char	*result;
	int		i;

	result = malloc((ft_strlen(str) + 1) * sizeof(char));
	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			result[i] = str[i] + 32;
		else
			result[i] = str[i];
		i++;
	}
	return (result);
}

int	exec_parent(t_mini *mini, char **line)
{
	if (!ft_strcmp("unset", line[0]))
		mini->exit_status = unset(line, &mini->env);
	else if (!ft_strcmp("export", line[0]))
		mini->exit_status = export(line, &mini->env);
	else if (!ft_strcmp("cd", line[0]))
		mini->exit_status = cd(line[1], &mini->env);
	else if (!ft_strcmp("exit", line[0]))
		mini->exit_status = exit_builtin(line, mini->exit_status);
	else
		return (-1);
	if (mini->exit_status == ENOMEM)
		ft_exit(mini, NULL, NULL, ENOMEM);
	return (mini->exit_status);
}

int	exec_builtin(t_mini *mini, char **line)
{
	char	*lower;

	lower = to_lower(line[0]);
	if (!ft_strcmp("echo", lower))
		mini->exit_status = echo(line);
	else if (!ft_strcmp("pwd", lower))
		mini->exit_status = pwd(mini->env);
	else if (!ft_strcmp("env", lower))
		mini->exit_status = environment(mini->env);
	else if (!ft_strcmp("unset", line[0]))
		mini->exit_status = unset(line, &mini->env);
	else if (!ft_strcmp("export", line[0]))
		mini->exit_status = export(line, &mini->env);
	else if (!ft_strcmp("cd", line[0]))
		mini->exit_status = cd(line[1], &mini->env);
	else if (!ft_strcmp("exit", line[0]))
		mini->exit_status = exit_builtin(line, mini->exit_status);
	else
		return (free(lower), -1);
	free(lower);
	if (mini->exit_status == ENOMEM)
		ft_exit(mini, NULL, NULL, ENOMEM);
	return (mini->exit_status);
}
