/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchanaa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:12:18 by bchanaa           #+#    #+#             */
/*   Updated: 2023/11/05 15:28:08 by bchanaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_handleclear(void (*del)(void *), void *nc, int sc, t_list **nl)
{
	if (del && nc)
		del(nc);
	if (sc && nl)
		ft_lstclear(nl, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*curr;
	void	*newcontent;

	if (!lst || !f)
		return (NULL);
	newcontent = f(lst->content);
	newlst = ft_lstnew(newcontent);
	if (!newlst)
		return (ft_handleclear(del, newcontent, 0, NULL));
	curr = newlst;
	lst = lst->next;
	while (lst)
	{
		newcontent = f(lst->content);
		curr->next = ft_lstnew(newcontent);
		if (!curr->next)
			return (ft_handleclear(del, newcontent, 1, &newlst));
		lst = lst->next;
		curr = curr->next;
	}
	return (newlst);
}
