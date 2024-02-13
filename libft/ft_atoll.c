/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:38:52 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/13 16:43:24 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *str)
{
	int				sign;
	long long		resulttemp;
	long long		result;

	sign = 1;
	result = 0;
	resulttemp = 0;
	while (*str == 32 || (*str < 14 && *str > 8))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		result = resulttemp * 10 + (*str++ - 48);
		if (result < resulttemp && sign == 1)
			return (-1);
		if (result < resulttemp && sign == -1)
			return (0);
		resulttemp = result;
	}
	return (result * sign);
}
