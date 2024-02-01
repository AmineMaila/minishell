/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:36:38 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/01 18:16:01 by mmaila           ###   ########.fr       */
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
