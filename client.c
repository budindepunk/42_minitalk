/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:39:03 by csilva-r          #+#    #+#             */
/*   Updated: 2024/07/19 18:34:39 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	num;

	if (nptr[0] == '\0')
		return (0);
	num = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = (num * 10) + (nptr[i] - '0');
		i++;
	}
	return (num * sign);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	char_to_bit(char c, int pid)
{
	int	i;

	i = 8;
	while (--i >= 0)
	{
		if (c & 0x01)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c >>= 1;
		usleep(100);
	}
}

void	int_to_bit(int n, int pid)
{
	int	i;

	i = 32;
	while (--i >= 0)
	{
		if (n & 0x01)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		n >>= 1;
		usleep(100);
	}
}

int	main(int argc, char *argv[])
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		int_to_bit(ft_strlen(argv[2]), pid);
		while (argv[2][i])
		{
			char_to_bit(argv[2][i], pid);
			i++;
		}
		char_to_bit('\0', pid);
	}
	else
		write(1, "please run ./client <PID> <MESSAGE>\n", 37);
	return (0);
}
