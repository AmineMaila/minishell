/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:35:15 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/11 13:32:18 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}

static	size_t	word_len(const char *str, char *charset)
{
	int		len;
	char	quote;

	len = 0;
	while (str[len] && !is_charset(str[len], charset))
	{
		if (str[len] == 34 || str[len] == 39)
		{
			quote = str[len++];
			while (str[len] && str[len] != quote)
				len++;
			if (!str[len])
				return (len);
		}
		len++;
	}
	return (len);
}

static size_t	word_count(char const *s, char *charset)
{
	size_t	i;
	size_t	count;
	char	quote;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (is_charset(s[i], charset) && s[i])
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && !is_charset(s[i], charset))
		{
			if (s[i] == 34 || s[i] == 39)
			{
				quote = s[i++];
				while (s[i] && s[i] != quote)
					i++;
				if (!s[i])
					break ;
			}
			i++;
		}
	}
	return (count);
}

static char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
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

char	**split(char const *s, char *charset)
{
	char		**result;
	size_t		words_count;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	words_count = word_count(s, charset);
	result = (char **) malloc((words_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < words_count)
	{
		while (*s && is_charset(*s, charset))
			s++;
		result[i] = (char *)malloc(word_len(s, charset) + 1);
		if (!result[i])
			return (free_2d(&result), NULL);
		ft_strncpy(result[i], (char *)s, word_len(s, charset));
		result[i++][word_len(s, charset)] = '\0';
		s = s + word_len(s, charset);
	}
	result[i] = NULL;
	return (result);
}
