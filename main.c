/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:46:25 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/17 20:08:47 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"

void	minishell_init(t_minishell *minishell, char **env)
{
	minishell->exit_status = 0;
	minishell->input = NULL;
	minishell->cmd_line = NULL;
	minishell->cmd_table = NULL;
	minishell->env = NULL;
	minishell->lst = NULL;
	minishell_env(minishell, env);
}

void	read_cmd_line(t_minishell *minishell)
{
	minishell->input = readline("minishell-4.81$ ");
	if (minishell->input)
		add_history(minishell->input);
	else
	{
		ft_exit(minishell, NULL, NULL, 0);
		exit (0);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		minishell;

	(void)argc;
	(void)argv;
	if (!isatty(0))
		return (ft_putstr_fd("minishell: input is not a terminal\n", 2), -1);
	signals_handler();
	minishell_init(&minishell, env);
	while (1)
	{
		read_cmd_line(&minishell);
		// if (!(*minishell.input))
		// 	continue ;
		input_lexer(&minishell);
		// ft_print_matrix(minishell.cmd_line);
		parse(&minishell);
		// printf("%s\n", minishell.input);
	}
}
