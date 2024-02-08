/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:35:46 by mmaila            #+#    #+#             */
/*   Updated: 2023/12/24 17:30:53 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/pipex.h"

char	*ft_realloc(char *buf, int xtrsize)
{
	char	*tmp;

	if (!buf)
	{
		buf = malloc(1);
		if (!buf)
			return (NULL);
		buf[0] = '\0';
	}
	tmp = ft_strdup(buf);
	free(buf);
	if (!tmp)
		return (NULL);
	buf = malloc(ft_strlen(tmp) + xtrsize + 1);
	if (!buf)
	{
		free(tmp);
		return (NULL);
	}
	ft_strcpy(buf, tmp);
	free(tmp);
	return (buf);
}

char	*package(char **chyata, char *buf, char *readbuf)
{
	int	i;
	int	j;

	i = 0;
	while (readbuf[i] != '\n' && readbuf[i])
		i++;
	if (readbuf[i])
		i++;
	buf = ft_realloc(buf, i);
	if (!buf)
	{
		free(*chyata);
		*chyata = NULL;
		return (NULL);
	}
	ft_strncat(buf, readbuf, i);
	j = 0;
	while (readbuf[i])
		(*chyata)[j++] = readbuf[i++];
	(*chyata)[j] = '\0';
	return (buf);
}

char	*chyatacheck(char *chyata, char **readbuf)
{
	if (chyata)
		ft_strcpy(*readbuf, chyata);
	else
	{
		chyata = malloc((size_t)(BUFFER_SIZE) + 1);
		if (!chyata)
		{
			free(*readbuf);
			return (NULL);
		}
	}
	return (chyata);
}

char	*readfile(char	**chyata, char *buf, char **readbuf, int fd)
{
	int	bread;

	bread = ft_strlen(*readbuf);
	if (!(*readbuf)[0])
		bread = read(fd, *readbuf, BUFFER_SIZE);
	while (bread > 0)
	{
		(*readbuf)[bread] = '\0';
		buf = package(chyata, buf, *readbuf);
		if (!buf)
		{
			free(*readbuf);
			return (NULL);
		}
		if (newline(buf))
		{
			free(*readbuf);
			return (buf);
		}
		bread = read(fd, *readbuf, BUFFER_SIZE);
	}
	free(*readbuf);
	free(*chyata);
	*chyata = NULL;
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*chyata = NULL;
	char		*readbuf;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readbuf = malloc((size_t)(BUFFER_SIZE) + 1);
	if (!readbuf || read(fd, readbuf, 0) == -1)
	{
		if (readbuf)
			free(readbuf);
		if (chyata)
			free(chyata);
		chyata = NULL;
		return (NULL);
	}
	readbuf[0] = '\0';
	chyata = chyatacheck(chyata, &readbuf);
	if (!chyata)
		return (NULL);
	buf = NULL;
	buf = readfile(&chyata, buf, &readbuf, fd);
	if (!buf)
		return (NULL);
	return (buf);
}
