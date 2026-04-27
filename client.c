/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouifr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:16:13 by mobouifr          #+#    #+#             */
/*   Updated: 2024/04/26 16:26:01 by mobouifr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	v;
	int		s;

	i = 0;
	v = 0;
	s = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		v = v * 10 + (str[i] - 48);
		i++;
	}
	while (str[i] != '\0')
		if (!ft_isdigit(str[i++]))
			return (write (2, "BAD INPUT\n", 10));
	return (v * s);
}

void	incrypted_msg(char c, int pid)
{
	int		i;
	char	c2;

	i = 7;
	while (i >= 0)
	{
		c2 = c >> i;
		if ((c2 & 1) == 0)
		{
			kill(pid, SIGUSR1);
		}
		else if ((c2 & 1) == 1)
		{
			kill(pid, SIGUSR2);
		}
		i--;
		usleep(200);
	}
}

int	main(int argc, char *argv[])
{
	int	pid;
	int	i;

	i = 0;
	if (argc != 3 || argv[1][0] == '-')
	{
		write (2, "BAD INPUT\n", 10);
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 1 && pid >= -1)
	{
		write (2, "BAD INPUT\n", 10);
		exit(1);
	}
	while (argv[2][i])
	{
		incrypted_msg (argv[2][i], pid);
		i++;
		usleep(200);
	}
	incrypted_msg ('\0', pid);
	return (0);
}
