/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/19 15:27:20 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"
/*
legenda: 
n = 1 (è file)
n = 2	(è argomento)
n = 11 (è la builtin echo)
n = 12 (è la builtin cd)
n = 13 (è la builtin pwd)
n = 14 (è la builtin export)
n = 15 (è la builtin unset)
n = 16 (è la builtin env)
n = 17 (è la builtin exit)
n = 20 (è un command trovato che esiste e si trova in $PATH) 
n = 2 (è una pipe "|")
n = 7 (è una redirecion ">")
n = 3 (è una redirecion "<")
n = 4 (è una redirecion ">>")
n = 9 (è un here document "<<")

*/

//controlla se la pipe ha qulcosa a destra, le pipe non contano
int check_redir_errors(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->tkn[i])
	{
		if (mini->tkn[i] <= 9 && mini->tkn[i] >= 3)
		{
			if (mini->tkn[i + 1] && mini->tkn[i + 1] != PIPE)
				mini->tkn[i + 1] = 1;
			else
			{
				g_exit = 2; //unexpected token
				return (0);
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

//trova quote aperte
int err_quote(t_mini *mini)
{
	int i;
	
	i = 0;
	while (mini->commands[i])
	{
		if (mini->commands[i][0] == D_QUOT || mini->commands[i][0] == QUOT)
		{
			if (mini->commands[i][0] == D_QUOT && (ft_strlen(mini->commands[i])-1))
			{
				if(mini->commands[i][ft_strlen(mini->commands[i])-1] != D_QUOT)
					return(0);
			}
			else if(mini->commands[i][0] == QUOT && (ft_strlen(mini->commands[i])-1))
			{
				if (mini->commands[i][ft_strlen(mini->commands[i])-1] != QUOT)
					return(0);
			}
		}
		i++;
	}
	return (1);
}

int check_errors(t_mini *mini)
{
	if (!err_quote(mini))
	{
		g_exit = 127;
		return (0);
	}
	if (!check_redir_errors(mini))
		return (0);
	if (!check_pipe_errors(mini))
		return (0);
	if (!check_cmds(mini))
		return (1);
	return (1);
}

