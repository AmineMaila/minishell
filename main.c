/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:46:25 by mmaila            #+#    #+#             */
/*   Updated: 2024/01/31 23:16:43 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"

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

int main(int argc, char **argv, char **env)
{
	t_minishell		minishell;
	t_list_parse	*lst;

	lst = NULL;
	signal(SIGINT, interrupt);
	while (1)
	{
		read_cmd_line(&minishell);
		input_lexer(&minishell);
		parse(minishell.cmd_line, env);
		print_parse(lst);
	}
}
