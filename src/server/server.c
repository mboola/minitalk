
#include "minitalk.h"

static void	convert_bits(int sig, siginfo_t *info, void *ucontext)
{
	static char				c = 0;
	static unsigned char	bits = 0;

	c |= ((sig == SIGUSR1) << bits);
	bits++;
	if (bits == 8)
	{
		ft_printf(1, "%c", c);
		bits = 0;
		c = 0;
	}
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
	int		server_pid;
	struct	sigaction	s_sigaction;

	server_pid = (int)getpid();
	ft_printf(1, "%d\n", server_pid);
	s_sigaction.sa_sigaction = convert_bits;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while(1)
		pause();
	return (0);
}
