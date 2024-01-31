/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:05:44 by mmaila            #+#    #+#             */
/*   Updated: 2024/01/31 13:21:19 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"


t_list_parse	*ft_lstnew(char *str)
{
	t_list_parse	*lst;

	lst = (t_list_parse *) malloc(sizeof(t_list_parse));
	if (lst == NULL)
		return (NULL);
	lst->str = str;
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd_back(t_list_parse **lst, char *str)
{
	t_list_parse	*temp;
	t_list_parse	*new;

	new = ft_lstnew(str);
	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_list_parse	*parse(char **str)
{
	int				i;
	t_list_parse	*result;
	
	result = NULL;
	i = 0;
	while (str[i])
		ft_lstadd_back(&result, str[i++]);
	return (result);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_list_parse	*lst;
	char *arr[] = {"cat", "infile", "|", "ls", "-a", "|", "wc", "-l", NULL};
	
	lst = parse(arr);
	flag(lst, env);
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
		else if (lst->flag == FLAG)
		{
			printf("\033[0;35m");
			printf("FLAG");
			printf("\033[0m");
		}
		else if (lst->flag == FILEE)
		{
			printf("\033[0;32m");
			printf("FILE");
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
		printf("]-");
		lst = lst->next;
	}
}