/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:46:25 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/21 22:23:16 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"

void	mini_init(t_mini *mini, char **env)
{
	mini->exit_status = 0;
	mini->syntax = 0;
	mini->input = NULL;
	mini->cmd_line = NULL;
	mini->table = NULL;
	mini->env = NULL;
	mini->lst = NULL;
	mini->pids = NULL;
	mini_env(mini, env);
}

void	read_cmd_line(t_mini *mini)
{
	mini->input = readline(MSH MSG);
	if (mini->input)
		add_history(mini->input);
	else
	{
		printf("exit\n");
		ft_exit(mini, NULL, NULL, 0);
		exit(mini->exit_status);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini		mini;

	(void)argc;
	(void)argv;
	if (!isatty(0))
		return (ft_putstr_fd("minishell: input is not a terminal\n", 2), 1);
	mini_init(&mini, env);
	while (1)
	{
		signals_handler();
		read_cmd_line(&mini);
		input_lexer(&mini);
		parse(&mini);
		ft_exit(&mini, NULL, NULL, 0);
	}
}
