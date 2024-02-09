/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:24:17 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/08 19:03:25 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void print_open_file_descriptors() {
    int max_fd = getdtablesize(); // Get the maximum number of file descriptors
    printf("Open file descriptors:\n");
    for (int fd = 0; fd < max_fd; fd++) {
        if (fcntl(fd, F_GETFD) != -1 || errno != EBADF) { // Check if the file descriptor is valid
            printf("%d\n", fd);
        }
    }
}

void	birth(t_data *pipex, t_cmd_table *table)
{
	int	fd[2]; // < infile cat -e | wc -l > outfile

	if (pipe(fd) == -1)
		ft_exit(NULL, NULL, errno);
	if (table[pipex->index].outfd == -42)
		table[pipex->index].outfd = fd[1];
	else
		close(fd[1]);
	pipex->pids[pipex->id_count] = fork();
	if (pipex->pids[pipex->id_count] == -1)
		ft_exit(NULL, NULL, errno);
	if (pipex->pids[pipex->id_count] == 0)
	{
		if (table[pipex->index].infd == -1 || table[pipex->index].outfd == -1)
			exit(0);
		printf("{%d}\n",table[pipex->index].infd);
		printf("{%d}\n",table[pipex->index].outfd);
		close(fd[0]);
		if (dup2(table[pipex->index].infd, 0) == -1)
			ft_exit(NULL, NULL, errno);
		print_open_file_descriptors();
		close (table[pipex->index].infd);
		if (dup2(table[pipex->index].outfd, 1) == -1)
			ft_exit(NULL, NULL, errno);
		close(table[pipex->index].outfd);
		if (execve(table[pipex->index].line[0], table[pipex->index].line, NULL) == -1)
			ft_exit(NULL, NULL, errno);
	}
	pipex->id_count++;
	close(table[pipex->index].infd);
	if (!pipex->outstatus && table[pipex->index + 1].infd == -42)
		table[pipex->index + 1].infd = fd[0];
	close(table[pipex->index].outfd);
}

void	spawn_children(t_data *pipex, t_cmd_table *table, int cmds)
{
	while (pipex->index < cmds)
	{
		if (pipex->index == cmds - 1)
			pipex->outstatus = 1;
		birth(pipex, table);
		pipex->index++;
	}
	close(table[pipex->index].infd);
	pipex->index = 0;
	while (pipex->index < pipex->id_count)
	{
		if (waitpid(pipex->pids[pipex->index++], 0, 0) == -1)
			ft_exit(NULL, NULL, errno);
	}
	free(pipex->pids);
}

void	pipex_init(t_data *pipex, int cmds)
{
	pipex->id_count = 0;
	pipex->heredoc = 0;
	pipex->outstatus = 0;
	pipex->pids = malloc(cmds * sizeof(int));
}

int	execute(t_cmd_table *table, int cmds)
{
	t_data	pipex;

	pipex_init(&pipex, cmds);
	pipex.index = 0;
	// if (!ft_strcmp(argv[1], "here_doc"))
	// {
	// 	if (argc < 6)
	// 		ft_exit(NULL, "insufficient arguments", 1);
	// 	pipex.heredoc = 1;
	// 	pipex.infd = here_doc(argv[2], &pipex);
	// 	pipex.index = 3;
	// }
	// else
		// pipex.infd = open(argv[1], O_RDONLY);
	spawn_children(&pipex, table, cmds);
	exit(0);
}

int main()
{
	t_cmd_table *table;
	char *arr[] = {"cat", "-e", NULL};

	table = malloc(3 * sizeof(t_cmd_table));
	table[0].line = arr;
	table[0].infd = open("infile", O_RDONLY);
	table[0].outfd = -42;
	
	char *arr2[] = {"wc", "-l", NULL};
	table[1].line = arr2;
	table[1].infd = -42;
	table[1].outfd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
	table[2].line = NULL;
	execute(table, 2);
}
