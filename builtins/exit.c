/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:20:08 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/21 12:46:50 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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

int	exit_builtin(char **args, long long exit_code)
{
	int				argc;

	argc = len_2d(args);
	if (argc == 1)
		(printf("exit\n"), exit(exit_code));
	else if (argc > 2 && str_is_digit(args[1]))
		return (print_error("exit", "too many arguments"), 1);
	else if (argc > 1 && !str_is_digit(args[1]))
		return (printf("exit\n"),
			ft_exit(NULL, args[1], "numeric argument required", 255), 1);
	exit_code = ft_atoll(args[1]);
	if ((ft_strlen(args[1]) > 1 && (exit_code == 0 || exit_code == -1)))
		return (printf("exit\n"),
			ft_exit(NULL, args[1], "numeric argument required", 255), 1);
	printf("exit\n");
	exit((unsigned char)exit_code);
}
