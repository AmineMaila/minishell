/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:46:25 by mmaila            #+#    #+#             */
/*   Updated: 2024/01/29 20:57:43 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h> 
# include <fcntl.h>
# include <signal.h>

void	read_loop()
{
	char	*input;
	
	input = readline("minishell-4.81$ ");
	while (input)
	{
		add_history(input);
		if (!strcmp(input, "exit"))
			exit(EXIT_SUCCESS);
		free(input);
		input = readline("minishell-4.81$ ");
	}
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
	signal(SIGINT, interrupt);
	read_loop();
}
