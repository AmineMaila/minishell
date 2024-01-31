/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:32:02 by nazouz            #+#    #+#             */
/*   Updated: 2023/11/09 17:44:31 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_count_words(const char *str, char c)
{
	size_t		count;

	count = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
		{
			count++;
			while (*str && *str != c)
				str++;
		}
	}
	return (count);
}

static	size_t	ft_word_len(const char *str, char c)
{
	int		len;

	len = 0;
	while (*str && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

static char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static	void	*ft_free_array(char **array, int n)
{
	while (n--)
		free(array[n]);
	free(array);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char		**result;
	size_t		words_count;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	words_count = ft_count_words(s, c);
	result = (char **)malloc((words_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < words_count)
	{
		while (*s && *s == c)
			s++;
		result[i] = (char *)malloc(ft_word_len(s, c) + 1);
		if (!result[i])
			return (ft_free_array(result, i));
		ft_strncpy(result[i], (char *)s, ft_word_len(s, c));
		result[i++][ft_word_len(s, c)] = '\0';
		s = s + ft_word_len(s, c);
	}
	result[i] = 0;
	return (result);
}
