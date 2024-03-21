/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:22:30 by luca              #+#    #+#             */
/*   Updated: 2024/03/21 17:56:49 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_cd(t_node *node, t_mini *mini)
{
	int	i;
	char *old_pwd;

	i = 0;
	old_pwd = getcwd(NULL, 0);
	if (chdir(node->cmd_matrix[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", node->cmd_matrix[1]);
		return ;
	}
	else
	{
		while(ft_strnstr(mini->en[i], "PWD", 3) == NULL)
			i++;
		mini->en[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
		i = 0;
		while(ft_strnstr(mini->en[i], "OLDPWD", 6) == NULL)
			i++;
		mini->en[i] = ft_strjoin("OLDPWD=", old_pwd);
	}
	return ;
}

void	ft_echo(t_node *node, t_mini *mini)
{
	int space;
	int i;

	space = 0;
	i = 1;
	if (node->cmd_matrix[1] == NULL)
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
		printf("%s\n", mini->en[i]);
		i++;
	}
}

int	check_space(char *str)
{
	int		i;
	bool	space;

	i = 0;
	space = false;
	while(str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 1)
			return(-1);
		if (str[i] == '=')
			space = true;
		i++;
	}
	if (space == false)
		return (-1);
	return(0);
}
void	create_variable(char *str, t_mini *mini)
{
	int	i;
	char *temp;

	i = 0;
	while(str[i] != '=')
		i++;
	temp = ft_substr(str, 0, i + 1);
	if (ft_getenv(mini->en, temp) == NULL)
	{
		i = 0;
		while(mini->en[i])
			i++;
		mini->en[i] = ft_strdup(temp);
		mini->en[i + 1] = NULL;
	}
	else
	{
		i = 0;
		while(ft_strnstr(mini->en[i], temp, ft_strlen(temp)) == NULL)
			i++;
		mini->en[i] = ft_strdup(str);
	}
}

void	ft_export(t_node *node, t_mini *mini)
{
	int	i;

	i = 1;
	while(node->cmd_matrix[i])
	{
		if (check_space(node->cmd_matrix[i]) == -1)
			ft_putendl_fd("Invalid export variable\n", 2);
		create_variable(node->cmd_matrix[i], mini);
		i++;
	}

}
