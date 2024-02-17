/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:19:34 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/16 20:29:49 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	is_nflag(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while(str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	echo(char **line)
{
	int nflag;
	int	i;

	nflag = 0;
	i = 1;
	while (is_nflag(line[i]))
	{
		nflag = 1;
		i++;
	}
	while (line[i])
	{
		printf("%s", line[i]);
		if (line[i + 1])
			printf(" ");
		i++;
	}
	if (!nflag)
		printf("\n");
}
