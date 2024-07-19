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

void	signal_handler(int signal)
{
	static int	char_received;
	static int	signals_received;
	char		c;

	if (signal == SIGUSR1)
		char_received += 1 << signals_received;
	signals_received++;
	if (signals_received == 8)
	{
		if (char_received == 0)
			write(1, "\n", 1);
		else
		{
			c = (char)char_received;
			write(1, &c, 1);
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
