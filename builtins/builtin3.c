/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:58:58 by luca              #+#    #+#             */
/*   Updated: 2024/04/03 18:23:48 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	**copy_matrix_extend(char **original, const char *new_str)
{
	int		length;
	int		i;
	char	**copy;

	i = 0;
	length = 0;
	while (original[length] != NULL)
		length++;
	copy = malloc(sizeof(char *) * (length + 2));
	while (i < length)
	{
		copy[i] = strdup(original[i]);
		i++;
	}
	copy[length] = strdup(new_str);
	copy[length + 1] = NULL;
	return (copy);
}

void	add_string_and_reallocate(char ***matrix, const char *new_str)
{
	char	**new_matrix;

	new_matrix = copy_matrix_extend(*matrix, new_str);
	free_matrix(*matrix);
	*matrix = new_matrix;
}

void	create_variable(char *str, t_mini *mini)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	temp = ft_substr(str, 0, i);
	if (ft_getenv(mini->en, temp) == NULL)
	{
		i = 0;
		while (mini->en[i])
			i++;
		add_string_and_reallocate(&mini->en, str);
	}
	else
	{
		i = 0;
		while (ft_strnstr(mini->en[i], temp, ft_strlen(temp)) == NULL)
			i++;
		free(mini->en[i]);
		mini->en[i] = ft_strdup(str);
	}
	free(temp);
}

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

void	ft_export(t_node *node, t_mini *mini)
{
	int	i;
	int	p;

	p = 0;
	if (node->cmd_matrix[1] == NULL)
	{
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
		return ;
	}
	i = 1;
	while (node->cmd_matrix[i])
	{
		if (check_space(node->cmd_matrix[i], node, mini) == 1)
			return ;
		create_variable(node->cmd_matrix[i++], mini);
	}
}
