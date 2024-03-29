/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/03/20 19:57:37 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

/*
int ft_unset_0(t_mini *mini, char **mtr)
{
	int i;
	int t;
	
	i = 1;
	t = 0;
	if (!mtr[i])
		return (0);
	
	while (mtr[i])
	{
		printf("--------------%s\n", ft_getenv(mini->en, mtr[i]));
		if (ft_getenv(mini->en, mtr[i]))
			t++;
		i++;
	}
	if (t == 1)
	{
		return (0);
	}
	else
	{
		printf("-------------------------------------------------%d\n", t);
		return (t);
	}
}
void swapMatrix(char ***str1, char ***str2)
{
	char *temp = *str1;

	*str1 = *str2;
	*str2 = temp;
}

void ft_unset(t_mini *mini, char **mtr)
{
	int i;
	char **newenv;
	int t;
	int z;

	t = 1;
	z = 0;
	i = ft_unset_0(mini, mtr);
	newenv = NULL;
	if (!i)
		return;
	newenv = malloc(sizeof(char *) * (count_matrix(mini->en) - i + 1));
	i = 0;
	while (mini->en[i])
	{
		if (ft_strncmp(newenv[i], mtr[t], ft_strlen(mtr[t] - 1)))//ogni volta che controlla aumenta
			t++;
		else
		{
			newenv[z] = ft_strdup(mini->en[i]); //nel caso in cui è da copiare è gia aumentato, quindi guarda quello prima
			z++;
		}
		i++;
	}
	newenv[z] = NULL;
	swapMatrix(&mini->en, &newenv);
	//free_matrix(mini->en);
	printf("-------------------------------------------------");
}

*/

void ft_unset(t_mini *mini, char **mtr)
{
	int i;
	int j;

	i = 1;
	while(mtr[i])
	{
		j = 0;
		while(mini->en[j])
		{
			if(!ft_strncmp(mini->en[j], mtr[i], ft_strlen(mtr[i])))
			{
				free(mini->en[j]);
				while (mini->en[j])
				{
					mini->en[j] = mini->en[j + 1];
					j++;
				}
				break;
			}
			j++;
		}
		i++;
	}
}