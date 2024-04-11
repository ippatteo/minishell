/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 04:49:36 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/11 04:58:23 by mcamilli         ###   ########.fr       */
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

void	ft_export(t_node *node, t_mini *mini)
{
	int	i;
	int	p;

	p = 0;
	if (node->cmd_matrix[1] == NULL)
	{
		i = 0;
		ft_print_export(mini);
		g_exit = 0;
		return ;
	}
	i = 1;
	while (node->cmd_matrix[i])
	{
		if (check_space(node->cmd_matrix[i], node, mini) == 1)
		{
			g_exit = 0;
			return ;
		}
		create_variable(node->cmd_matrix[i++], mini);
	}
	g_exit = 0;
}
