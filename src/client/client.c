
#include "minitalk.h"

static void	convert_and_send_bits(int server_pid, char c)
{
	char	bits;
	unsigned char	mask;

	mask = 1;
	bits = 8;
	while (bits > 0)
	{
		//printf("%u ", c & 0x1);
		if (c & 0x1)
			kill(server_pid, SIGURS1);
		else
			kill(server_pid, SIGURS2);
		c >>= 1;
		bits--;
	}
}

/*
 *	Client will be executed with two arguments: server_pid and string to send.
 *	If the arguments are not valid, comunication does not start.
 *	Client converts each character to bits and sends them one by one
 *	using the signals SIGURS1 (bit 1) or SIGUSR2 (bit 0).
 */
int main(int argc, char **argv)
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
	}
	return (0);
}
