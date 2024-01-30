/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:46:25 by mmaila            #+#    #+#             */
/*   Updated: 2024/01/30 17:24:34 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	interrupt()
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

int main(void)
{
	t_minishell		minishell;

	signal(SIGINT, interrupt);
	while (1)
	{
		read_cmd_line(&minishell);
		tokenize_input(&minishell);
		// ft_print_matrix(minishell.cmd_line);
	}
}
