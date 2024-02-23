/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:01:48 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:01:58 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_timeout	g_timeout;

static void	reset_values(char *c, unsigned char *bits)
{
	*c = 0;
	*bits = 0;
}

static void	convert_bits(int sig, siginfo_t *info, void *ucontext)
{
	static char				c = 0;
	static unsigned char	bits = 0;
	int						err;

	(void)info;
	(void)ucontext;
	if (!g_timeout.activated)
	{
		reset_values(&c, &bits);
		g_timeout.activated = 1;
	}
	g_timeout.cycles = 0;
	c |= ((sig == SIGUSR1) << bits);
	bits++;
	if (bits == 8)
	{
		if (c == END_CHAR)
			g_timeout.activated = 0;
		else
		{
			ft_putchar_err(1, c, &err);
			reset_values(&c, &bits);
		}
	}
	kill(info->si_pid, SIGUSR1);
}

/*
 *	When we start the server, the PID of the server will be displayed so
 *	clients can comunicate with it with signals.
 *	The server will be awaiting to signals to come.
 *	When a signal is recieved, it will either be 
 *	SIGUSR1 (bit 1) or SIGUSR2 (bit 0).
 *	The server will convert each 8 bits to a character and display it.
 */
int	main(void)
{
	int					server_pid;
	struct sigaction	s_sigaction;

	server_pid = (int)getpid();
	ft_printf(1, "%d\n", server_pid);
	s_sigaction.sa_sigaction = convert_bits;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	g_timeout.activated = 0;
	g_timeout.cycles = 0;
	while (1)
	{
		usleep(10);
		if (g_timeout.activated)
		{
			g_timeout.cycles++;
			if (g_timeout.cycles == MAX_TIMEOUT)
				g_timeout.activated = 0;
		}
	}
	return (0);
}
