/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:46:42 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/10 13:18:02 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	ft_lstadd_back(t_list_parse **lst, char *str)
{
	t_list_parse	*temp;
	t_list_parse	*new;

	new = ft_lstnew(str);
	new->flag = 0;
	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
