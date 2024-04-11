/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:22:30 by luca              #+#    #+#             */
/*   Updated: 2024/04/11 04:57:31 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	change_cwd(t_mini *mini, char *old_pwd)
{
	int		i;
	char	*cur_cwd;

	cur_cwd = getcwd(NULL, 0);
	i = 0;
	if (ft_getenv(mini->en, "PWD") != NULL)
	{
		while (ft_strnstr(mini->en[i], "PWD", 3) == NULL)
			i++;
		free(mini->en[i]);
		mini->en[i] = ft_strjoin("PWD=", cur_cwd);
	}
	i = 0;
	if (ft_getenv(mini->en, "OLDPWD") != NULL)
	{
		while (ft_strnstr(mini->en[i], "OLDPWD", 6) == NULL)
			i++;
		free(mini->en[i]);
		mini->en[i] = ft_strjoin("OLDPWD=", old_pwd);
	}
	free(old_pwd);
	free(cur_cwd);
}

void	ft_cd(t_node *node, t_mini *mini)
{
	char	*old_pwd;

	old_pwd = ft_strdup(ft_getenv(mini->en, "PWD"));
	if (!node->cmd_matrix[1])
	{
		if (ft_getenv (mini->en, "HOME") == NULL)
		{
			free(old_pwd);
			g_exit = 1;
			ft_putendl_fd("cd : HOME not set", 2);
			return ;
		}
		chdir(ft_getenv(mini->en, "HOME"));
	}
	else if (chdir(node->cmd_matrix[1]) == -1)
	{
		free(old_pwd);
		g_exit = 1;
		ft_putendl_fd("cd: No such file or directory", 2);
		return ;
	}
	change_cwd(mini, old_pwd);
	g_exit = 0;
	return ;
}

void	ft_echo(t_node *node, t_mini *mini) //gexit nel parse
{
	int	space;
	int	i;

	space = 0;
	i = 1;
	if (node->cmd_matrix == NULL)
	{
		printf("\n");
		return ;
	}
	if (node->cmd_matrix[1] && ft_strncmp(node->cmd_matrix[1], "-n", 2) == 0)
	{
		space = -1;
		i = 2;
	}
	while (node->cmd_matrix[i] != NULL)
	{
		printf("%s", node->cmd_matrix[i]);
		if (node->cmd_matrix[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (space == 0)
		printf("\n");
}

void	ft_pwd(t_node *node, t_mini *mini) //g_exit nel parser
{
	int	i;

	i = 0;
	if (ft_getenv(mini->en, "PWD") == NULL)
		return ;
	while (ft_strnstr(mini->en[i], "PWD", 3) == NULL)
		i++;
	printf("%s\n", mini->en[i] + 4);
}

void	ft_env(t_node *node, t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->en[i] != NULL)
	{
		if (ft_strchr(mini->en[i], '='))
			printf("%s\n", mini->en[i]);
		i++;
	}
	g_exit = 0;
}
