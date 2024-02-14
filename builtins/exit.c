/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:20:08 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/14 13:53:35 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	get_2d_size(char **array)
{
	int			i;

	if (!array || !array[0])
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}
int	str_is_digit(char *str)
{
	int			i;

	i = 0;
	if (str[0] != '+' && str[0] != '-' && !ft_isdigit(str[0]))
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(char **args)
{
	int				argc;
	long long		exit_code;

	exit_code = 0; // last exit status
	argc = get_2d_size(args);
	if (argc > 2)
		return (ft_exit("exit", ": too many arguments", 0), 0);
	if (argc == 2)
	{
		exit_code = ft_atoll(args[1]);
		printf("exit_code = %lld\nstrlen = %zu\nstr_is_digit = %d\n", exit_code, ft_strlen(args[1]), str_is_digit(args[1]));
		if ((ft_strlen(args[1]) > 1 && (exit_code == 0 || exit_code == -1))
			|| !str_is_digit(args[1]))
			return (ft_exit(args[1], ": numeric argument required", 0), 0);
	}
	exit(0);
}