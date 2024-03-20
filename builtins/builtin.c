/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:22:30 by luca              #+#    #+#             */
/*   Updated: 2024/03/20 15:22:19 by lpicciri         ###   ########.fr       */
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

void	change_variable(char *str, t_mini *mini)
{
	int	i;
	char *temp;

	i = 0;
	while(str[i] != '=')
		i++;
	temp = malloc(sizeof(char) * i + 1);
	i = 0;
	while(str[i] != '=')
	{
		temp[i] = str[i];
		i++;
	}
	while(ft_strnstr(mini->en[i], temp, ft_strlen(temp)) == NULL)
		i++;
	free(mini->en[i]);
	mini->en[i] = ft_strdup(str);
}

int	create_insert(char *str, t_mini *mini)
{
	int	i;

	i = 0;
	while(mini->en[i])
		i++;
	mini->en[i] = ft_strdup(str);
}

int	check_exist(char *str, t_mini *mini)
{
	char *temp;
	int	i;

	i = 0;
	while(str[i] != '=')
		i++;
	temp = malloc(sizeof(char) * i + 1);
	i = 0;
	while(str[i] != '=')
	{
		temp[i] = str[i];
		i++;
	}
	temp[i + 1] = '\0';
	if (ft_getenv(mini->en, temp) == NULL)
		return(0);
	change_variable(str, mini);
	return(-1);
}

int	check_space(char *str)
{
	int	i;
	bool	single_space;

	i = 0;
	single_space = false;
	while(str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 1)
			return(-1);
		if (str[i] == '=')
		{
			if (i == 0 || str[i + 1] == '\0' || single_space == true)
				return (-1);
			single_space = true;
		}
		i++;
	}
	return(0);
}

void	ft_export(t_node *node, t_mini *mini)
{
	int	i;

	i = 1;
	while(node->cmd_matrix[i])
	{
		if (check_space(node->cmd_matrix[i]) == -1)
			return ;
		if (check_exist(node->cmd_matrix[i], mini) == 0)
			create_insert(node->cmd_matrix[i], mini);
	}

}
