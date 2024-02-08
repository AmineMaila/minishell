/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:05:44 by mmaila            #+#    #+#             */
/*   Updated: 2024/02/08 14:59:09 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

// void	split_line(t_list_parse *lst)
// {

// }

void	print_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd("`", 2);
	if (!str)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(str, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd("\n", 2);
}

int	syntax(t_list_parse *lst)
{
	int		i;

	i = 0;
	if (lst->flag == PIPE)
		return (print_error(lst->str), -1);
	while (lst)
	{
		if (lst->flag == ERR)
			return (print_error(lst->str), -1);
		if ((lst->flag == REDIN || lst->flag == REDOUT
				|| lst->flag == HEREDOC || lst->flag == APPEND))
		{
			if (lst->next == NULL)
				return (print_error(NULL), -1);
			else if (lst->next->flag == PIPE)
				return (print_error(lst->next->str), -1);
		}
		if ((lst->flag == PIPE && lst->next == NULL)
			|| (lst->flag == PIPE && lst->next->flag == PIPE))
			return (print_error(lst->str), -1);
		lst = lst->next;
	}
	return (0);
}

void	parse(char **str, char **env)
{
	int				i;
	t_list_parse	*lst;

	lst = NULL;
	i = 0;
	while (str[i])
		ft_lstadd_back(&lst, str[i++]);
	flag(&lst, env);
	if (syntax(lst) == -1)
	{
		ft_lstclear(&lst);
		free(str);
		return ;
	}
	//split_line(lst);
	//execute();
	print_parse(lst);
	ft_lstclear(&lst);
	free(str);
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
		else if (lst->flag == HEREDOC)
		{
			printf("\033[1;36m");
			printf("HEREDOC");
			printf("\033[0m");
		}
		else if (lst->flag == APPEND)
		{
			printf("\033[1;37m");
			printf("APPEND");
			printf("\033[0m");
		}
		printf("]-");
		lst = lst->next;
	}
	printf("\n");
}
