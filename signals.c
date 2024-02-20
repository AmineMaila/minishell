/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:44:05 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/20 16:06:28 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"

void	sig_quit(int signum)
{
	ft_putstr_fd("Quit: ", 2);
	ft_putnbr_fd(signum, 2);
	ft_putchar_fd('\n', 2);
}

void	sig_int(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sigint_cmd(int signum)
{
	(void)signum;
	printf("\n");
	exit(7);
}

void	signals_handler(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}
