/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:03:44 by mmaila            #+#    #+#             */
/*   Updated: 2023/12/29 12:51:19 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_data
{
	char	*outpath;
	int		*pids;
	int		infd;
	int		outfd;
	int		id_count;
	int		outstatus;
	int		index;
	int		heredoc;
}				t_data;

# define BUFFER_SIZE 10

// libft
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strlen(const char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strncat(char *dest, const char *src, unsigned int nb);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

// get_next_line
char	*get_next_line(int fd);
int		newline(char *buf);

// command
void	get_cmd(char ***cmd_line, char *cmd, char **env);
char	*get_path(char *cmd, char **env);
void	exec_cmd(char *cmd, char **env);

// heredoc
int		here_doc(char *lim, t_data *pipex);

// exit
void	ft_exit(char *cmd, char *str, int ext);
void	free_2d(char ***arr);

#endif