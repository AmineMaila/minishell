/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 22:41:01 by nazouz            #+#    #+#             */
/*   Updated: 2023/11/04 22:41:26 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	n_long;

	n_long = n;
	if (n_long < 0)
	{
		ft_putchar_fd('-', fd);
		n_long = n_long * (-1);
	}
	if (n_long < 10)
		ft_putchar_fd(n_long + 48, fd);
	if (n_long >= 10)
	{
		ft_putnbr_fd(n_long / 10, fd);
		ft_putnbr_fd(n_long % 10, fd);
	}
}
