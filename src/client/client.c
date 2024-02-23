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

static void	convert_and_send_bits(int server_pid, char c)
{
	char	bits;

	bits = 8;
	while (bits > 0)
	{
		if (c & 0x1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		c >>= 1;
		bits--;
		usleep(100);
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
		if (server_pid < 1)
			return (0);
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
