/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:43:13 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/07 16:05:47 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_operator(char c)
{
	if (c == '<'
		|| c == '>')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	*alloc_cpy(char *str, char **result, int n)
{
	n += ft_strlen(str);
	*result = malloc(sizeof(char) * (n + 1));
	if (!*result)
		return (NULL);
	ft_strlcpy(*result, str, n + 1);
	return (*result);
}
