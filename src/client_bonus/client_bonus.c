/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:01:48 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/13 11:01:58 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	g_ack;

static void	process_response(int sig, siginfo_t *info, void *ucontext)
{
	if (sig == SIGUSR1)
	{
		ft_printf(1, "ACK'd.\n");
		g_ack = 1;
	}
}

static void	wait_for_response(void)
{
	if (!g_ack)
		pause();
}

static void	convert_and_send_bits(int server_pid, char c)
{
	char				bits;
	struct sigaction	s_sigaction;

	s_sigaction.sa_sigaction = process_response;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	bits = 8;
	while (bits > 0)
	{
		g_ack = 0;
		if (c & 0x1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		c >>= 1;
		bits--;
		wait_for_response();
	}
}

/*
 *	Client will be executed with two arguments: server_pid and string to send.
 *	If the arguments are not valid, comunication does not start.
 *	Client converts each character to bits and sends them one by one
 *	using the signals SIGURS1 (bit 1) or SIGUSR2 (bit 0).
 */
int	main(int argc, char **argv)
{
	long	server_pid;
	char	*str;

	if (argc == 3 && argv[2][0] != '\0')
	{
		server_pid = ft_atoi(argv[1]);
		str = argv[2];
		while (*str != '\0')
		{
			convert_and_send_bits(server_pid, *str);
			str++;
		}
		convert_and_send_bits(server_pid, '\n');
		convert_and_send_bits(server_pid, END_CHAR);
	}
	return (0);
}
