/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaila <mmaila@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:11:02 by nazouz            #+#    #+#             */
/*   Updated: 2024/02/01 18:29:27 by mmaila           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	ft_lstdelone(t_list_parse *lst)
{
	if (!lst)
		return ;
	free(lst->str);
	free(lst);
}
