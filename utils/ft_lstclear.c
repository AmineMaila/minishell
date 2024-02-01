/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:40:51 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/01 18:16:25 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list		*current;
	t_list		*next;

	if (!lst || !(*lst) || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}
