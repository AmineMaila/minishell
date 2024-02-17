/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:46:25 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/17 21:25:28 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"

void	mini_init(t_mini *mini, char **env)
{
	mini->exit_status = 0;
	mini->input = NULL;
	mini->cmd_line = NULL;
	mini->table = NULL;
	mini->env = NULL;
	mini->lst = NULL;
	mini_env(mini, env);
}

void	read_cmd_line(t_mini *mini)
{
	mini->input = readline(MINISHELL);
	if (mini->input)
		add_history(mini->input);
	else
	{
		ft_exit(mini, NULL, NULL, 0);
		exit (0);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini		mini;

	(void)argc;
	(void)argv;
	if (!isatty(0))
		return (ft_putstr_fd("minishell: input is not a terminal\n", 2), -1);
	signals_handler();
	mini_init(&mini, env);
	while (1)
	{
		read_cmd_line(&mini);
		// if (!(*mini.input))
		// 	continue ;
		input_lexer(&mini);
		// ft_print_matrix(mini.cmd_line);
		parse(&mini);
		// printf("%s\n", mini.input);
	}
}
