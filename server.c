/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:54:07 by jbremser          #+#    #+#             */
/*   Updated: 2024/05/24 13:49:07 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define END_TRANSMISSION '\0'

static void	err_ex(char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	exit(1);
}

static void	print_msg(char **message)
{
	ft_printf("%s\n", *message);
	free(*message);
	*message = NULL;
}

static char	*msg_join(char *message, char curr_c)
{
	char	*final;
	char	add_c[2];

	if (!message)
		err_ex("Error: no message\n");
	add_c[0] = curr_c;
	add_c[1] = '\0';
	final = ft_strjoin(message, add_c);
	if (!final)
	{
		free(message);
		err_ex("Error: strjoin fail\n");
	}
	free(message);
	return (final);
}

void	handle_signal(int signal)
{
	static unsigned char	current_char = 0;
	static int				bit_index = 0;
	static char				*message;

	if (!message)
	{
		message = ft_strdup("");
		if (message == NULL)
			exit(1);
	}
	if (signal == SIGUSR1)
		current_char |= 1 << bit_index;
	else if (signal == SIGUSR2)
		current_char |= 0 << bit_index;
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == END_TRANSMISSION)
			print_msg(&message);
		else
			message = msg_join(message, current_char);
		bit_index = 0;
		current_char = 0;
	}
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause ();
	return (0);
}
