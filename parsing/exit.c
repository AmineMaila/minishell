/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:02:40 by mmaila            #+#    #+#             */
/*   Updated: 2024/01/30 15:52:09 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "../libft/libft.h"

void	ft_exit(char *cmd, char *str, int ext)
{
	if (str)
	{
		ft_putstr_fd("pipex: ", 2);
		if (cmd)
			ft_putstr_fd(cmd, 2);
		ft_putendl_fd(str, 2);
	}
	else
		perror("pipex");
	if (ext)
		exit(ext);
}
