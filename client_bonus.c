/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:08:50 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/24 16:11:53 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	send_signal(int pid, unsigned char character)
{
	int				i;
	unsigned char	temp_char;

	i = 0;
	temp_char = character;
	while (i < 8)
	{
		temp_char = character >> i;
		if (temp_char % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(42);
		i++;
	}
}

void	receive_signal(int signal)
{
	// (void)context;
	// (void)info;
	if (signal == SIGUSR1)
	{
		ft_printf("Server: message received \n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	client_sa;
	pid_t				server_pid;
	char				*message;
	int					i;

	i = 0;
	client_sa.sa_flags = SA_SIGINFO;
	client_sa.__sigaction_u.__sa_handler = receive_signal;
	sigemptyset(&client_sa.sa_mask);
	sigaction(SIGUSR1, &client_sa, NULL);
	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		message = argv[2];
		while (message[i])
			send_signal(server_pid, (unsigned char)message[i++]);
		send_signal(server_pid, '\0');
		pause();
	}
	else
		ft_printf("Error: invalid input: %s", argv[2]);
	return (0);
}
