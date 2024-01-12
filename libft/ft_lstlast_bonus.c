/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:03:51 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/05 15:29:28 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*prev;
	t_list	*curr;

	if (!lst)
		return (lst);
	curr = lst;
	prev = curr;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
	}
	return (prev);
}
