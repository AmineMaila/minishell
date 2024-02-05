/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:46:25 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/05 15:42:50 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"

void	minishell_init(t_minishell *minishell, t_list_parse	**lst)
{
	minishell->input = NULL;
	minishell->cmd_line = NULL;
	*lst = NULL;
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
	t_list_parse	*lst;

	(void)argc;
	(void)argv;
	(void)env;
	signal(SIGINT, interrupt);
	minishell_init(&minishell, &lst);
	while (1)
	{
		read_cmd_line(&minishell);
		input_lexer(&minishell);
		// free(minishell.input);
		ft_print_matrix(minishell.cmd_line);
		// printf("hh\n");
		// free_2d(&minishell.cmd_line);
		lst = parse(minishell.cmd_line, env);
		print_parse(lst);
		ft_lstclear(&lst);
	}
}
