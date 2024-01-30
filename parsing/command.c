/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:21:14 by mmaila            #+#    #+#             */
/*   Updated: 2024/01/30 16:12:03 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "../libft/libft.h"

void	free_2d(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free((*arr)[i++]);
	free(*arr);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4))
		i++;
	path = ft_split(env[i] + 5, ":");
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i++], cmd);
		if (!tmp)
			return (free_2d(&path), NULL);
		if (!access(tmp, F_OK | X_OK))
			return (free_2d(&path), tmp);
		free(tmp);
	}
	free_2d(&path);
	ft_exit(cmd + 1, ": command not found", 1);
	return (NULL);
}

int	is_cmd(char **token, char **env)
{
	char	*tmp;

	if (access(*token, F_OK | X_OK))
	{
		tmp = ft_strjoin("/", *token);
		if (!tmp)
			ft_exit(NULL, NULL, errno);
		*token = get_path(tmp, env);
		if (!(*token))
			return (0);
		free(tmp);
	}
	return (1);
}

int	is_flag(char *token)
{
	if (token[0] == '-')
		return (1);
	return (0);
}

int	is_pipe(char *token)
{
	if (token[0] == '|')
		return (1);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *arr = "ls";

	is_cmd(&arr, env);
	printf("%d\n", is_pipe("|cat"));
	printf("%s\n", arr);
}