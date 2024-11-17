/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matteocamilli <matteocamilli@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/11/17 10:25:33 by matteocamil      ###   ########.fr       */
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
		{	printf("ELECTRICITY has been shut down\n");
			sleep(2);
			printf("accessing emergency radars\n");
			sleep(4);
			printf("scanning starship...\n");
			sleep(4);
			printf("NON-human life forms found\n");
			sleep(2);
			printf("looking for positions\n");
			sleep(4);
			printf("loading NON-human EGGS on radar\n");
			sleep(4);
			printf("loading NON-human MOTHER on radar\n");
			sleep(4);
			printf("an EMERGENCY signal has been sent\n");
			sleep(4);
			printf("SURVIVE until rescue\n");
			sleep(4);
			printf("LAUNCHING...\n");
			sleep(10);

		}
	}
	return (0);
}
