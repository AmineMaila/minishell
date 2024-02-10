/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:46:25 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/10 12:40:01 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"

void	minishell_init(t_minishell *minishell)
{
	minishell->input = NULL;
	minishell->cmd_line = NULL;
}

void	read_cmd_line(t_minishell *minishell)
{
	minishell->input = readline("minishell-4.81$ ");
	if (minishell->input)
	{
		add_history(minishell->input);
		if (!strcmp(minishell->input, "exit"))
			exit(EXIT_SUCCESS);
	}
	else
		exit(EXIT_SUCCESS);
}

void	interrupt(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		minishell;

	(void)argc;
	(void)argv;
	signal(SIGINT, interrupt);
	minishell_init(&minishell);
	while (1)
	{
		read_cmd_line(&minishell);
		if (!(*minishell.input))
			continue ;
		input_lexer(&minishell);
		// ft_print_matrix(minishell.cmd_line);
		parse(&minishell, env);
	}
}
