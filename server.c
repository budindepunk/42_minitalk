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

void	print_reset(char *str, int *signals_received, int *flag)
{
	int	i;

	printf("i am in print reset \n");
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	free(str);
	str = NULL;
	*flag = 0;
	*signals_received = 0;
}

void	receive_len(int *flag, int signal, char **str)
{
	static int	info_received;
	static int	len;

	if (signal == SIGUSR1)
		len += 1 << info_received;
	info_received++;
	if (info_received == 32)
	{
		*flag = 1;
		printf("received len: %i\n", len);
		*str = calloc((len + 1), sizeof(char));
		info_received = 0;
		len = 0;
	}
}

void	signal_handler(int signal)
{
	static int	char_received;
	static int	signals_received;
	static int	len_flag;
	static char	*str;
	static int	i;

	if (!len_flag)
		receive_len(&len_flag, signal, &str);
	else
	{
		if (signal == SIGUSR1 && len_flag)
			char_received += 1 << signals_received;
		signals_received++;
		if (signals_received == 8 && len_flag)
		{
			if (char_received == 0)
			{
				i = 0;
				return (print_reset(str, &signals_received, &len_flag));
			}
			else
			{
				str[i++] = (char)char_received;
				char_received = 0;
			}
			signals_received = 0;
		}
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
