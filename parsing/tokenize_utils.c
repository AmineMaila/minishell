/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:43:13 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/04 19:55:01 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_operator(char c)
{
	if (c == '<'
		|| c == '>'
		|| c == '|')
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
