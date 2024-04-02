/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/04/02 19:27:29 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int check_redir_errors(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->tkn[i])
	{
		if (mini->tkn[i] <= 9 && mini->tkn[i] >= 3)
		{
			if (mini->tkn[i + 1] && mini->tkn[i + 1] != PIPE)
			{
				mini->tkn[i + 1] = 1;

			}
			else
			{
				g_exit = 2; //unexpected token
				return (1);
			}
		}
		i++;
	}
	return (1);
}

//controlla che le pipe siano non prime e non ultime
int check_pipe_errors(t_mini *mini)
{
	int i;
	int flag_found_cmd;

	i = 1;
	flag_found_cmd = 0;
	if (mini->tkn[0] == PIPE)
	{
		g_exit = 2;
		return (0);
	}
	while (mini->tkn[i])
	{
		if (mini->tkn[i] == PIPE)
		{
			if (!mini->tkn[i + 1])
			{
				g_exit = 2;
				return (0);
			}
		}
		i++;
	}
	return (1);
}
int check_cmds_2(t_mini *mini,int i, int flag_found_cmd)
{
	while (mini->tkn[i])
	{
		if ((mini->tkn[i] <= COMMAND && mini->tkn[i] >= BUILTIN || mini->tkn[i] == 1)
			&& !(mini->tkn[i-1] <= 9 && mini->tkn[i-1] >= 3))
		{
			if (mini->tkn[i] == 1 && flag_found_cmd == 0)
			{
				g_exit = 127;
				return (0);
			}
			if(flag_found_cmd == 0)
				flag_found_cmd = 1;
			else
				mini->tkn[i] = ARGS;
		}
		else if (mini->tkn[i] == PIPE)
			flag_found_cmd = 0;
		i++;
	}
	return (1);
}
//controlla che ci sia un comando e che esista,
//poi assegna un token a tutti gli argomenti dopo
//questo per ogni comando tr pipes
int check_cmds(t_mini *mini)
{
	int i;
	int flag_found_cmd;

	i = 1;
	flag_found_cmd = 0;
	if (mini->tkn[0] == 1)
	{
		g_exit = 127; //CMD NOT FOUND
		return (0);
	}
	if (mini->tkn[0] <= COMMAND && mini->tkn[0] >= BUILTIN)
		flag_found_cmd = 1;
	if (check_cmds_2(mini, i, flag_found_cmd))
		return (1);
	else
		return (0);
}

int check_errors(t_mini *mini)
{

	if (!check_redir_errors(mini))
		return (0);
	if (!check_cmds(mini))
		return (0);
	return (1);
}

