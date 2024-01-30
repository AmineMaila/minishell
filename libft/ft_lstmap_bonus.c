/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:00:04 by nazouz            #+#    #+#             */
/*   Updated: 2023/11/09 17:11:10 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list			*new_list;
	t_list			*current;
	t_list			*new_node;
	void			*f_result;

	if (!lst || !f || !del)
		return (NULL);
	current = lst;
	new_list = NULL;
	while (current != NULL)
	{
		f_result = f(current->content);
		new_node = ft_lstnew(f_result);
		if (new_node == NULL)
		{
			del(f_result);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}
