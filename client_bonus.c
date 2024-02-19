/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:28:31 by mes-salh          #+#    #+#             */
/*   Updated: 2024/02/13 16:28:32 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	sigal_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		write(1, "the mesaage was sent successfully\n", 34);
		exit(0);
	}
}

void	send_bit(int pid, char bit)
{
	int	sig;

	if (bit == '0')
		sig = SIGUSR1;
	else
		sig = SIGUSR2;
	kill (pid, sig);
	usleep(400);
}

void	send_char(int pid, char c)
{
	int		i;
	char	bit;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			bit = '1';
		else
			bit = '0';
		send_bit (pid, bit);
		i--;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;
	int		i;

	if (argc != 3)
	{
		write(2, "Usage: ./client PID message\n", 28);
		return (1);
	}
	signal(SIGUSR1, sigal_handler);
	i = 0;
	message = argv[2];
	pid = atoi(argv[1]);
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
	send_char(pid, '\0');
	while (1)
		pause();
	return (0);
}
