/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-salh <mes-salh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:29:24 by mes-salh          #+#    #+#             */
/*   Updated: 2024/03/03 18:03:49 by mes-salh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_header(void)
{
	ft_putstr_fd("\033[38;2;0;255;0m", 1);
	ft_putstr_fd("███████╗███████╗██████╗ ██╗   ██╗███████╗██████╗ \n", 1);
	ft_putstr_fd("██╔════╝██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗\n", 1);
	ft_putstr_fd("███████╗█████╗  ██████╔╝██║   ██║█████╗  ██████╔╝\n", 1);
	ft_putstr_fd("╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝██╔══╝  ██╔══██╗\n", 1);
	ft_putstr_fd("███████║███████╗██║  ██║ ╚████╔╝ ███████╗██║  ██║\n", 1);
	ft_putstr_fd("╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝\n", 1);
	ft_putstr_fd("██████╗  ██████╗ ███╗   ██╗██╗   ██╗███████╗\n", 1);
	ft_putstr_fd("██╔══██╗██╔═══██╗████╗  ██║██║   ██║██╔════╝\n", 1);
	ft_putstr_fd("██████╔╝██║   ██║██╔██╗ ██║██║   ██║███████╗\n", 1);
	ft_putstr_fd("██╔══██╗██║   ██║██║╚██╗██║██║   ██║╚════██║\n", 1);
	ft_putstr_fd("██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████║\n", 1);
	ft_putstr_fd("╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝\n", 1);
	ft_putstr_fd("                    PID : ", 1);
	ft_putnbr(getpid());
	ft_putchar('\n');
	ft_putstr_fd("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n", 1);
	ft_putstr_fd("\033[0m", 1);
}

void	mes_handlesig(int sig, siginfo_t *info, void *just)
{
	static int		bit;
	static char		c;
	static int		pid;

	(void)just;
	if (pid != info->si_pid)
	{
		bit = 0;
		c = 0;
	}
	c = c << 1 | (sig - SIGUSR1);
	bit++;
	if (bit == 8)
	{
		if (c == 0)
			kill(info->si_pid, SIGUSR1);
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
	}
	pid = info->si_pid;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = mes_handlesig;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, 0) == -1 || sigaction(SIGUSR2, &sa, 0) == -1)
	{
		ft_putstr_fd("Error\n", 1);
		exit(1);
	}
	ft_header();
	while (1)
		pause();
	return (0);
}
