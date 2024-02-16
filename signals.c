/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:44:05 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/16 13:53:15 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/minishell.h"

void	sig_quit(int signum)
{
	(void)signum;
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sig_int(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	signals_handler(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}
