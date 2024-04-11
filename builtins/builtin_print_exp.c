/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_print_exp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 04:49:50 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/11 04:55:20 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_exp_qutes(char *c)
{
	int	i;

	i = 0;
	write(1, "declare -x ", 12);
	while (c[i] && c[i] != '=')
		write(1, &c[i++], 1);
	if (c[i] == '=')
		write(1, &c[i], 1);
	return (i);
}

void ft_print_export(t_mini *mini)
{
	int p;
	int i;

	p = 0;
	i = 0;
	while (mini->en[i] != NULL)
	{
		p = ft_exp_qutes(mini->en[i]);
		if (mini->en[i][p])
			printf("\"%s\"\n", mini->en[i] + (p + 1));
		else
			printf("\n");
		i++;
	}
}