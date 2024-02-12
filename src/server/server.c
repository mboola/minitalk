
# include <unistd.h>
#include <stdio.h>

int	main(void)
{
	long	server_pid;

	server_pid = (long)getpid();
	printf("%ld\n", server_pid);
	while(1)
	{
		
	}
	return (0);
}
