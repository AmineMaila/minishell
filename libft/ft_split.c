/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:17:46 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/04 12:41:38 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}

static size_t	word_count(char const *s, char *charset)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (is_charset(s[i], charset) && s[i])
			i++;
		if (s[i] != '\0')
			count++;
		while (!is_charset(s[i], charset) && s[i])
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


static int	alloc(char **str, char const *s, char *charset, size_t start)
{
	size_t	j;
	size_t	pivot;

	pivot = 0;
	j = 0;
	while (s[pivot])
	{
		while (is_charset(s[pivot], charset) && s[pivot])
			pivot++;
		start = pivot;
		while (!is_charset(s[pivot], charset) && s[pivot])
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

char	**ft_split(char const *s, char *charset)
{
	char	**str;
	size_t	start;

	start = 0;
	if (s == NULL)
		return (NULL);
	str = (char **) malloc((word_count(s, charset) + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	if (alloc(str, s, charset, start) == 0)
	{
		free(str);
		return (NULL);
	}
	str[word_count(s, charset)] = 0;
	return (str);
}
