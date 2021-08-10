/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biohazard <biohazard@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 10:39:27 by mmondell          #+#    #+#             */
/*   Updated: 2021/08/05 08:55:21 by biohazard        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_talk.h"

/*
*	the bit variable is used to know the positions of bits set to 1 or 0.
*
*	the 8th bit is used for unicode char.
*	Common printable characters stops at 127 (7 bits) in the ascii table.
*
*	kill is used to send the signal to the server process id.
*
*	(c & (1 << bit)) --> & is used to check if the bit at a certain position
*	in char c is set to 1.
*	if it is, send SIGUSR1. If the bit is not set (0) send SIGUSR2
*/
void	send_bit(char c, pid_t p_id)
{
	int	bit;
	int	ret;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			ret = kill(p_id, SIGUSR1);
		else
			ret = kill(p_id, SIGUSR2);
		if (ret == -1)
		{
			ft_putstr_fd("ERROR.", 1);
			exit(1);
		}
		usleep(50);
		bit++;
	}
}

/*
*	Displays a message on signal return from Server.
*/
void	msg_ack(int sig)
{
	(void)sig;
	write(1, "\033[32mMESSAGE ACKNOWLEDGED. CLOSING CLIENT\n", 42);
	exit(0);
}

/*
*	Simple function to send the message char by char to be deconstructed
*	in bits.
*/
void	send_message_char(char *str, pid_t p_id)
{
	while (*str)
	{
		send_bit(*str, p_id);
		str++;
	}
	send_bit('\0', p_id);
}

/*
*	Declare a variable pid_t that contains the server process id
*	to send the message passed in the argument.
*
*	if the number of arguments is different than 3, output error message.
*/
int	main(int ac, char **av)
{
	pid_t				process_id;

	if (ac != 3)
	{
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(" [PROCESS_ID] [MESSAGE]\n", 2);
		exit(1);
	}
	signal(SIGUSR1, msg_ack);
	process_id = ft_atoi(av[1]);
	send_message_char(av[2], process_id);
	exit(0);
}
