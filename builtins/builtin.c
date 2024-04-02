/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:22:30 by luca              #+#    #+#             */
/*   Updated: 2024/04/02 16:02:19 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	change_cwd(t_mini *mini, char *old_pwd)
{
	int	i;

	i = 0;
	if (ft_getenv(mini->en, "PWD") != NULL)
	{
		while(ft_strnstr(mini->en[i], "PWD", 3) == NULL)
			i++;
		mini->en[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
	}
	i = 0;
	if (ft_getenv(mini->en, "OLDPWD") != NULL)
	{
		while(ft_strnstr(mini->en[i], "OLDPWD", 6) == NULL)
			i++;
		mini->en[i] = ft_strjoin("OLDPWD=", old_pwd);
	}
}

void	ft_cd(t_node *node, t_mini *mini)
{
	int	i;
	char *old_pwd;

	i = 0;
	if (chdir(node->cmd_matrix[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", node->cmd_matrix[1]);
		return ;
	}
	else
		change_cwd(mini, old_pwd);
	return ;
}

void	ft_echo(t_node *node, t_mini *mini)
{
	int space;
	int i;

	space = 0;
	i = 1;
	if (node->cmd_matrix == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(node->cmd_matrix[1], "-n" , 2) == 0)
	{
		space = -1;
		i = 2;
	}
	while(node->cmd_matrix[i] != NULL)
	{
		printf("%s", node->cmd_matrix[i]);
		printf(" ");
		i++;
	}
	if (space == 0)
		printf("\n");
}

void	ft_pwd(t_node *node, t_mini *mini)
{
	int	i;

	i = 0;
	while(ft_strnstr(mini->en[i], "PWD", 3) == NULL)
		i++;
	printf("%s\n", mini->en[i] + 4);
}

void	ft_env(t_node *node, t_mini *mini)
{
	int	i;

	i = 0;
	while(mini->en[i] != NULL)
	{
		if (ft_strchr(mini->en[i], '='))
			printf("%s\n", mini->en[i]);
		i++;
	}
}
