/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:46:25 by mmaila            #+#    #+#             */
/*   Updated: 2024/01/29 18:23:05 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

void	sigint_handler();

void	prompt()
{
	char	*input;

	input = readline("minishell-4.81$ ");
	if (input && *input)
	{
		add_history(input);
		if (!strcmp(input, "exit"))
			exit(EXIT_SUCCESS);
		free(input);
	}
}

void	read_loop()
{
	while (1)
		prompt();
}

void	sigint_handler()
{
	write(1, "\n", 1);
	read_loop();
	return ;
	// prompt();
	// printf("you pressed CTRL+C\n");
}

int main(void)
{
	signal(SIGINT, sigint_handler);
	read_loop();
}
