/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:05:44 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/05 18:41:57 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

t_list_parse	*parse(char **str, char **env)
{
	int				i;
	t_list_parse	*result;

	result = NULL;
	i = 0;
	while (str[i])
		ft_lstadd_back(&result, str[i++]);
	flag(&result, env);
	return (result);
}

void	print_parse(t_list_parse *lst)
{
	while (lst)
	{
		printf("[");
		if (lst->flag == COMMAND)
		{
			printf("\033[0;31m");
			printf("COMMAND");
			printf("\033[0m");
		}
		else if (lst->flag == PIPE)
		{
			printf("\033[0;33m");
			printf("PIPE");
			printf("\033[0m");
		}
		else if (lst->flag == FILEE)
		{
			printf("\033[1;30m");
			printf("FILE");
			printf("\033[0m");
		}
		else if (lst->flag == ARG)
		{
			printf("\033[0;32m");
			printf("ARG");
			printf("\033[0m");
		}
		else if (lst->flag == REDIN)
		{
			printf("\033[1;34m");
			printf("RED-IN");
			printf("\033[0m");
		}
		else if (lst->flag == REDOUT)
		{
			printf("\033[1;34m");
			printf("RED-OUT");
			printf("\033[0m");
		}
		else if (lst->flag == DQUOTE)
		{
			printf("\033[0;34m");
			printf("DQUOTE");
			printf("\033[0m");
		}
		else if (lst->flag == ODQUOTE)
		{
			printf("\033[0;34m");
			printf("ODQUOTE");
			printf("\033[0m");
		}
		else if (lst->flag == SQUOTE)
		{
			printf("\033[0;34m");
			printf("SQUOTE");
			printf("\033[0m");
		}
		else if (lst->flag == OSQUOTE)
		{
			printf("\033[0;34m");
			printf("OSQUOTE");
			printf("\033[0m");
		}
		else if (lst->flag == TEXT)
		{
			printf("\033[0;35m");
			printf("TEXT");
			printf("\033[0m");
		}
		else if (lst->flag == VAR)
		{
			printf("\033[3;35m");
			printf("%s", lst->str);
			printf("\033[0m");
		}
		printf("]-");
		lst = lst->next;
	}
	printf("\n");
}
