/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:28:31 by mes-salh          #+#    #+#             */
/*   Updated: 2024/02/26 06:38:18 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sigal_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		write(1, "the mesaage was sent successfully\n", 34);
		exit(0);
	}
}

void	send_data(int pid, char data)
{
	int	i;
	int	sig;

	i = 7;
	while (i >= 0)
	{
		sig = SIGUSR1;
		if ((data >> i) & 1)
			sig = SIGUSR2;
		kill(pid, sig);
		usleep(500);
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
	if (argv[1][0] == '-')
		return (0);
	signal(SIGUSR1, sigal_handler);
	i = 0;
	message = argv[2];
	pid = atoi(argv[1]);
	while (message[i])
	{
		send_data(pid, message[i]);
		i++;
	}
	send_data(pid, '\0');
	while (1)
		pause();
	return (0);
}
