/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:17:42 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/10 11:28:05 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	is_lim(char **lim, int fd)
{
	char	*tmp;

	while (1)
	{
		ft_putstr_fd("> ", 0);
		tmp = get_next_line(0);
		if (!tmp)
		{
			free(*lim);
			close(fd);
			exit(0);
		}
		if (!ft_strcmp(*lim, tmp))
		{
			free(tmp);
			free(*lim);
			close(fd);
			exit(0);
		}
		ft_putstr_fd(tmp, fd);
		free(tmp);
	}
}

int	here_doc(char *lim)
{
	int		fd[2];
	int		id;

	if (pipe(fd) == -1)
		ft_exit(NULL, NULL, errno);
	id = fork();
	if (id == -1)
		ft_exit(NULL, NULL, errno);
	if (!id)
	{
		close(fd[0]);
		lim = ft_strjoin(lim, "\n");
		if (!lim)
			ft_exit(NULL, NULL, errno);
		is_lim(&lim, fd[1]);
	}
	close(fd[1]);
	waitpid(id, 0, 0);
	return (fd[0]);
}
