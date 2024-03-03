/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 23:05:43 by mes-salh          #+#    #+#             */
/*   Updated: 2024/03/03 15:39:05 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	i = 0;
	message = argv[2];
	pid = ft_atoi(argv[1]);
	while (message[i])
	{
		send_data(pid, message[i]);
		i++;
	}
	send_data(pid, '\0');
	return (0);
}
