/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:02:35 by rapetros          #+#    #+#             */
/*   Updated: 2022/10/08 16:06:26 by rapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	ft_putnbr(int number)
{
	char	c;

	if (number >= 0 && number <= 9)
	{
		c = number + 48;
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(number / 10);
		ft_putnbr(number % 10);
	}
}

int	all_zero(char *bin)
{
	int	i;

	i = 0;
	while (bin[i])
	{
		if (bin[i] == '1')
			return (0);
		i++;
	}
	return (1);
}

void	to_text(char *bin)
{
	int		i;
	int		base;
	int		res;
	char	c;

	i = 7;
	base = 1;
	res = 0;
	while (i >= 0)
	{
		if (bin[i] == '1')
			res += base;
		base *= 2;
		i--;
	}
	c = (char)res;
	write(1, &c, 1);
}

void	sig_h(int sig, siginfo_t *info, void *content)
{
	static int	i;
	static char	binary[9];

	binary[8] = '\0';
	if (sig == SIGUSR2)
		binary[i % 8] = '1';
	else if (sig == SIGUSR1)
		binary[i % 8] = '0';
	if ((i + 1) % 8 == 0 && all_zero(binary) == 1)
		kill(info->si_pid, SIGUSR1);
	else if (i && (i + 1) % 8 == 0)
		to_text(binary);
	i++;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sig_h;
	ft_putnbr(getpid());
	write(1, "\n", 1);
	while (1)
	{
		sigaction(SIGUSR1, &sa, 0);
		sigaction(SIGUSR2, &sa, 0);
		pause ();
	}
	return (0);
}
