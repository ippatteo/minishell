/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:47:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/04/02 19:54:57 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	inits(char **argv, int argc, t_mini *mini, char **env)
{
	(void)argv;
	(void)argc;
	init_mini(mini);
	copy_env(mini, env);
	signal_handler();
}
