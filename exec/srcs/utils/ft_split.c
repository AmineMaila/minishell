/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:17:46 by mmaila            #+#    #+#             */
/*   Updated: 2023/12/24 17:30:18 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/pipex.h"

static size_t	word_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static void	freemem(char **str, size_t j)
{
	size_t	k;

	k = 0;
	while (k < j)
		free(str[k++]);
}

static int	alloc(char **str, char const *s, char c, size_t start)
{
	size_t	j;
	size_t	pivot;

	pivot = 0;
	j = 0;
	while (s[pivot])
	{
		while (s[pivot] == c && s[pivot])
			pivot++;
		start = pivot;
		while (s[pivot] != c && s[pivot])
			pivot++;
		if (s[start] != '\0')
		{
			str[j] = (char *) malloc(pivot - start + 1);
			if (str[j] == NULL)
			{
				freemem(str, j);
				return (0);
			}
			ft_strlcpy(str[j++], s + start, pivot - start + 1);
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	start;

	start = 0;
	if (s == NULL)
		return (NULL);
	str = (char **) malloc((word_count(s, c) + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	if (alloc(str, s, c, start) == 0)
	{
		free(str);
		return (NULL);
	}
	str[word_count(s, c)] = 0;
	return (str);
}
