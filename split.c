# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}

static	size_t	ft_word_len(const char *str, char *charset)
{
	int		len;
	char	c;

	len = 0;
	if (*str != 34 && *str != 39)
	{
		printf("str[%c] != 34\n", *str);
		while (*str && !is_charset(*str, charset) && *str != 34)
			(len++, str++);
	}
	else
	{
		printf("str[%c] == 34\n", *str);
		c = *str;
		str++;
		len++;
		while (*str && *str != c)
		{
			printf("[%c]", *str);
			(len++, str++);
		}
		len++;
	}
	return (len);
}

int	handle_quotes(char *s, int i, char quote)
{
	i++;
	while (s[i] && s[i] != quote)
		i++;
	return (i);
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
		if (s[i] == 34 || s[i] == 39)
		{
			i = handle_quotes((char *)s, i, s[i]) + 1;
			continue;
		}
		while (!is_charset(s[i], charset) && s[i] && (s[i] != 34 || s[i] != 39))
			i++;
		printf("i = %d\n", i);
	}
	return (count);
}

static	void	*ft_free_array(char **array, int n)
{
	while (n--)
		free(array[n]);
	free(array);
	return (0);
}

char	**ft_split(char const *s, char *charset)
{
	char		**result;
	size_t		words_count;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	words_count = word_count(s, charset);
	printf("word_count = %d\n", (int)words_count);
	result = (char **) malloc((words_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < words_count)
	{
		printf("*s before [%c]\n", *s);
		while (*s && is_charset(*s, charset))
		{
			printf("[%c]", *s);
			s++;
		}
		printf("\n");
		int word_len = ft_word_len(s, charset);
		printf("[%d] word_len = %lu\n", i, word_len);
		result[i] = (char *)malloc(word_len + 1);
		printf("[%zu] malloc = %lu\n", i, word_len + 1);
		if (!result[i])
			return (ft_free_array(result, i));
		strncpy(result[i], (char *)s, word_len);
		result[i++][word_len] = '\0';
		s = s + word_len;
		printf("\n\n\n");
	}
	return (result);
}

int main(void)
{
	char *str = "aaa \'\"hello \'worl d  sss s\"";
	char **matrix;
	matrix = ft_split(str, " ");
	int i = 0;
	while (matrix[i] != NULL)
	{
		printf("[%s]\n", matrix[i]);
		i++;
	}
}