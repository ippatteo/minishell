/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:58:58 by luca              #+#    #+#             */
/*   Updated: 2024/04/02 20:45:36 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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


char **copy_matrix_extend(char **original, const char *new_str)
{
    int length = 0;
	int i;
	i = 0;
    while (original[length] != NULL) 
		length++; // Conta gli elementi

    // +2 per la nuova stringa e il terminatore NULL
    char **copy = malloc(sizeof(char *) * (length + 2));
    while (i < length) 
	{
        copy[i] = strdup(original[i]); 
		i++;// Copia ogni stringa
    }

    // Aggiunge la nuova stringa
    copy[length] = strdup(new_str);
    copy[length + 1] = NULL; // Imposta il terminatore NULL

    return copy;
}



void add_string_and_reallocate(char ***matrix, const char *new_str)
{
    char **new_matrix = copy_matrix_extend(*matrix, new_str);

    free_matrix(*matrix); // Libera l'originale

    *matrix = new_matrix; // Aggiorna il puntatore all'originale
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
		add_string_and_reallocate(&mini->en, str);
	}
	else
	{
		i = 0;
		while(ft_strnstr(mini->en[i], temp, ft_strlen(temp)) == NULL)
			i++;
		free(mini->en[i]);
		mini->en[i] = ft_strdup(str);
	}
	free(temp);
}

void	ft_export(t_node *node, t_mini *mini)
{
	int	i;
	
	if (node->cmd_matrix[1] == NULL)
	{
		i = 0;
		while(mini->en[i] != NULL)
		{
			printf("x - %s\n", mini->en[i]);
			i++;
		}
		return ;
	}
	i = 1;
	while(node->cmd_matrix[i])
	{
		if (check_space(node->cmd_matrix[i]) == -1)
			ft_putendl_fd("Invalid export variable\n", 2);
		create_variable(node->cmd_matrix[i], mini);
		i++;
	}
}
