/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:23:19 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/06 17:22:27 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char **s1, char c)
{
	size_t	start;
	size_t	end;
	char	*trimmed;

	if (!*s1 || !s1)
		return (NULL);
	if (!(*s1)[0])
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(*s1) - 1;
	while ((*s1)[start] && (*s1)[start] == c)
		start++;
	while (end > 0 && (*s1)[end] == c)
		end--;
	trimmed = ft_substr(*s1, start, end - start + 1);
	free(*s1);
	return (trimmed);
}
