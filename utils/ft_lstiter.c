/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:53:09 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/01 18:16:20 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list		*current;

	if (!lst || !f)
		return ;
	current = lst;
	while (current != NULL)
	{
		f(current->content);
		current = current->next;
	}
}
