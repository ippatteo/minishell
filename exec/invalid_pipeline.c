/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:42:39 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/11 06:05:14 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int valid_pipeline(t_node *node)
{
	int p;

	p = node->n_pipe;
	while (node->n_pipe == p || node)
	{
		if(node->this_tkn > 10 && node->this_tkn <= 20)
			return (1);
		if (node->next != NULL)
			node = node->next;
		else 
			break;
	}
	ft_putendl_fd("error : no command to input!", 2);
	return (0);
}