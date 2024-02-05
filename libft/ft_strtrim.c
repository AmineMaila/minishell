/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:23:19 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/05 16:30:07 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char **s1, char const *set)
{
	char	*result;
	size_t	end_index;
	int		i;

	if (!s1 || !*s1 || !set)
		return (NULL);
	i = 0;
	while ((*s1)[i] && ft_strchr(set, (*s1)[0]))
		i++;
	end_index = ft_strlen(*s1);
	while (end_index && ft_strchr(set, (*s1)[end_index - 1]))
		end_index--;
	result = (char *)malloc(((end_index + 1) * sizeof(char)));
	if (!result)
		return (NULL);
	ft_memcpy(result, (*s1), end_index);
	free(*s1);
	result[end_index] = '\0';
	return (result);
}
