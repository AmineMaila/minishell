/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:29:15 by nazouz            #+#    #+#             */
/*   Updated: 2023/11/08 19:13:11 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	to_allocate;

	to_allocate = ft_strlen(s1) + 1;
	result = (char *)malloc(to_allocate);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, to_allocate);
	return (result);
}
