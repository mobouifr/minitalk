/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:57:52 by mobouifr          #+#    #+#             */
/*   Updated: 2024/04/27 18:57:58 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int	n_zero_min(int nb)
{
	if (nb == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	return (0);
}

int	ft_putnbr(int nb)
{
	int	i;
	int	arr[10];
	int	count;

	i = 0;
	count = 0;
	if (nb == 0 || nb == -2147483648)
		return (n_zero_min(nb));
	if (nb < 0 && nb != -2147483648)
	{
		write(1, "-", 1);
		nb = nb * (-1);
		count = 1;
	}
	while (nb > 0)
	{
		arr[i] = (nb % 10) + 48;
		nb = nb / 10;
		i++;
		count++;
	}
	while (i > 0)
		write(1, &arr[--i], 1);
	return (count);
}

void	signal_handler(int signum)
{
	static char	c;
	static int	counter;

	if (signum == SIGUSR1)
	{
		c = c | 0;
	}
	else if (signum == SIGUSR2)
	{
		c = c | 1;
	}
	counter++;
	if (counter == 8)
	{
		if (c == '\0')
		{
			write (1, "\n", 1);
		}
		write(1, &c, 1);
		c = 0;
		counter = 0;
	}
	c = c << 1;
}

int	main(int argc, char *argv[])
{
	(void)argv;
	if (argc != 1)
	{
		write (2, "BAD INPUT\n", 10);
		exit (1);
	}
	write (1, "pid : ", 6);
	ft_putnbr(getpid());
	write (1, "\n", 1);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		;
	return (0);
}
