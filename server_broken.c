/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:41:30 by csilva-r          #+#    #+#             */
/*   Updated: 2024/07/15 21:08:48 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	print_reset(char **str, int *signals_received, int *flag)
{
	int	i;

	printf("i am in print reset \n");
	i = 0;
	while(str[i])
	{
		write(1, &str[i], 1);
	}
	write(1, "\n", 1);
	free(str);
	str = NULL;
	*flag = 0;
	*signals_received = 0;
}

void	receive_len(int *flag, int signal, char **str)
{
	static int	len;
	static int	i;
	
	if (signal == SIGUSR1)
		i += 1 << len;
	len++;
	if (len == 32)
	{
		*flag = 1;
		printf("received len: %i\n", i);
		*str = malloc(sizeof(char) * (len + 1));
	}
}

void	signal_handler(int signal)
{
	static int	char_received;
	static int	signals_received;

	static int	received_len_flag;
	static char	*str;
	static int	i;

	if (!received_len_flag)
	{
		printf("came in here because len flag is %d\n", received_len_flag);
		receive_len(&received_len_flag, signal, &str);
	}
	if (signal == SIGUSR1 && received_len_flag)
	{
		char_received += 1 << signals_received;
	}
	signals_received++;
	if (signals_received == 8 && received_len_flag)
	{
		printf("received %d signals\n", signals_received);
		if (char_received == 0)
		{
			printf("char received is 0\n");
			return (print_reset(&str, &signals_received, &received_len_flag));
		}
		else
		{
			printf("received char %c\n", (char)char_received);
			str[i++] = (char)char_received;
			char_received = 0;
		}
		signals_received = 0;
	}
}

int	main(void)
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	printf("my process ID is %i\n", getpid());
	while (1)
		pause();
	return (0);
}

