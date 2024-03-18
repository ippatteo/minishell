/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:21:24 by mcamilli          #+#    #+#             */
/*   Updated: 2024/03/15 17:24:50 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_lstadd_front(t_node **lst, t_node *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}
