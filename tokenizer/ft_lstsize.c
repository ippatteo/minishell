/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:24:30 by mcamilli          #+#    #+#             */
/*   Updated: 2024/03/15 17:26:10 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_lstsize(t_node *lst)
{
	t_node	*p;
	int		i;

	i = 0;
	p = lst;
	if (!lst)
		return (0);
	while (p != NULL)
	{
		p = p -> next;
		i++;
	}
	return (i);
}
