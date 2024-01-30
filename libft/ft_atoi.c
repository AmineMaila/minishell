/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:08:37 by nazouz            #+#    #+#             */
/*   Updated: 2023/11/09 23:44:20 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				sign;
	long			result;
	long			resulttemp;

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
