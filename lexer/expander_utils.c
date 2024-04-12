/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:04:25 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/11 14:06:19 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	semaphore_quotes(char d, t_mini *mini)
{
	mini->sub = NULL;
	if (d == D_QUOT && !mini->open_d_quot && !mini->open_quot)
		mini->open_d_quot = 1;
	else if (d == D_QUOT && mini->open_d_quot && !mini->open_quot)
		mini->open_d_quot = 0;
	if (d == QUOT && !mini->open_quot && !mini->open_d_quot)
		mini->open_quot = 1;
	else if (d == QUOT && mini->open_quot && !mini->open_d_quot)
		mini->open_quot = 0;
}

int	ft_it_is_exp_valid_2(int q, int count_exp)
{
	if (!q)
		return (count_exp + 1);
	else if (q == count_exp + 3)
		return (count_exp + 3);
	else if (q > count_exp + 3)
		return (0);
}

int	check_env(char c, char d)
{
	if (c == '$' && d && (ft_isalnum(d) || ft_isalpha(d) || d == '_'))
		return (0);
	return (-1);
}
