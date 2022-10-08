/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:02:26 by rapetros          #+#    #+#             */
/*   Updated: 2022/10/08 16:05:42 by rapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	long int	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == '\r' || *str == '\t' || *str == '\f' \
		|| *str == '\n' || *str == '\v' || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			res = (res * 10) + ((int)*str) - 48;
		else
			break ;
		str++;
	}
	return (res * sign);
}

void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
		write(1, "Message received.", 17);
}

void	send_zero(int pid_p)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		kill(pid_p, SIGUSR1);
		usleep(80);
		i--;
	}
}

int	main(int argc, char **argv)
{
	int	pid_p;
	int	i;
	int	j;

	if (argc < 3 || argc > 3)
		exit (1);
	signal(SIGUSR1, sig_handler);
	pid_p = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		j = 7;
		while (j >= 0)
		{
			if (argv[2][i] & 1 << j)
				kill(pid_p, SIGUSR2);
			else
				kill(pid_p, SIGUSR1);
			usleep(100);
			j--;
		}
		i++;
	}
	send_zero(pid_p);
	return (0);
}
