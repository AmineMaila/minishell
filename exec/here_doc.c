/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:17:42 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/20 16:18:15 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	is_lim(t_mini *mini, char **lim, int fd)
{
	char	*tmp;
	int		count;

	while (1)
	{
		ft_putstr_fd("> ", 0);
		tmp = get_next_line(0);
		if (!tmp || !ft_strcmp(*lim, tmp))
		{
			if (tmp)
				free(tmp);
			free(*lim);
			close(fd);
			ft_exit(mini, NULL, NULL, 0);
			exit(0);
		}
		count = envvar_count(tmp);
		while (count--)
			expand_var(mini, &tmp);
		ft_putstr_fd(tmp, fd);
		free(tmp);
	}
}

int	here_doc(t_mini *mini, char *lim)
{
	int	fd[2];
	int	id;
	int	status;

	signal(SIGINT, SIG_IGN);
	if (pipe(fd) == -1)
		ft_exit(mini, NULL, NULL, errno);
	id = fork();
	if (id == -1)
		ft_exit(mini, NULL, NULL, errno);
	if (!id)
	{
		close(fd[0]);
		lim = ft_strjoin(lim, "\n");
		if (!lim)
			ft_exit(mini, NULL, NULL, ENOMEM);
		signal(SIGINT, sigint_cmd);
		is_lim(mini, &lim, fd[1]);
	}
	close(fd[1]);
	waitpid(id, &status, 0);
	mini->exit_status = WEXITSTATUS(status);
	return (fd[0]);
}
