
#include "minitalk.h"

long client_id = 0;

static void	send_msg(long server_pid, char *str, long client_id)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	start_msg();
	while (i < len)
	{
		mask_and_send_msg(*(str + i), client_id);
		i++;
	}
	end_msg();
}

int main(int argc, char **argv)
{
	long	server_pid;
	long	curr_client_id;

	if (argc == 3)
	{
		curr_client_id = client_id;
		client_id++;
		server_pid = convert_pid(argv[1]);
		send_msg(server_pid, argv[2], client_id);
	}
	return (0);
}
