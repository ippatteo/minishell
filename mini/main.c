/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:23:29 by mcamilli          #+#    #+#             */
/*   Updated: 2024/02/14 14:42:52 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int main()
{
	char *prompt;
	while(1)
	{
		prompt = readline("minishell$ ");
		add_history(prompt); 
	}
}