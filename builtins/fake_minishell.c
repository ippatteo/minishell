/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matteocamilli <matteocamilli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/11/17 09:57:20 by matteocamil      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>


int	main(int argc, char **argv, char **env)
{
	
	while (1)
	{;
		char *cmd;
		cmd = readline("starshipShell$ ");
		if (cmd == NULL)
		{
			return (0);
		}
		if (*cmd != 0)
		{
			printf("launching radar...\n");
			sleep(2);
			printf("non human life form found\n");
		}
	}
	return (0);
}
