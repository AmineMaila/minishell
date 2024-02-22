/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:17:42 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/22 23:21:19 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	is_lim(t_mini *mini, char **lim, int fd)
{
	char	*tmp;
	int		count;

	signal(SIGINT, sigint_cmd);
	while (1)
	{
		ft_putstr_fd("> ", 0);
		tmp = get_next_line(0);
		if (!tmp || !ft_strcmp(*lim, tmp))
		{
			if (tmp)
				free(tmp);
			else
				printf("\n");
			free(*lim);
			close(fd);
			exit(0);
		}
		count = envvar_count(tmp);
		while (count--)
			expand_var(mini, &tmp);
		ft_putstr_fd(tmp, fd);
		free(tmp);
	}
}

int	here_doc(t_mini *mini, t_list_parse *next)
{
	int	fd[2];
	int	id;
	int	status;

	if (!next)
		return (fd[0]);
	signal(SIGINT, SIG_IGN);
	if (pipe(fd) == -1)
		ft_exit(mini, NULL, NULL, errno);
	id = fork();
	if (id == -1)
		ft_exit(mini, NULL, NULL, errno);
	if (!id)
	{
		close(fd[0]);
		next->str = ft_strjoin(next->str, "\n");
		if (!next->str)
			ft_exit(mini, NULL, NULL, ENOMEM);
		is_lim(mini, &next->str, fd[1]);
	}
	close(fd[1]);
	waitpid(id, &status, 0);
	mini->exit_status = WEXITSTATUS(status);
	return (fd[0]);
}
