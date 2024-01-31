/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 22:24:57 by nazouz            #+#    #+#             */
/*   Updated: 2023/11/07 23:14:28 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_count_digits(int n)
{
	size_t		result;

	result = 0;
	if (n < 0)
		result++;
	while (n)
	{
		n = n / 10;
		result++;
	}
	return (result);
}

static char	*ft_fill(char	*allocated_str, size_t	len, int n)
{
	unsigned int	n_cpy;

	n_cpy = n;
	if (n < 0)
		n_cpy = n * -1;
	allocated_str[len--] = '\0';
	while (len)
	{
		allocated_str[len--] = (n_cpy % 10) + 48;
		n_cpy = n_cpy / 10;
	}
	if (n < 0)
		allocated_str[0] = '-';
	else
		allocated_str[0] = n_cpy + 48;
	return (allocated_str);
}

char	*ft_itoa(int n)
{
	char				*result;
	size_t				to_allocate;

	if (!n)
		return (ft_strdup("0"));
	to_allocate = ft_count_digits(n);
	result = (char *)malloc((to_allocate + 1) * sizeof(char));
	if (!result)
		return (NULL);
	return (ft_fill(result, to_allocate, n));
}
