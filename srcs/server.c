/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biohazard <biohazard@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 14:11:05 by mmondell          #+#    #+#             */
/*   Updated: 2021/08/05 08:55:10 by biohazard        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_talk.h"

/*
*	declare static variable so they always stay on the stack.
*	we reconstruct de byte using the |= operator.
*	
*	You need siginfo_t struct to use si_pid to get the client process id
*	to send back a ACK signal.
*
*	Once bit reaches position 0 we write the reconstructed byte which
*	give the letter sent from the client until the message is fully decoded.
*/
void	decode(int sig, siginfo_t *info, void *ucontext)
{
	static int	bit = 0;
	static char	c = 0;
	int			ret;

	(void)ucontext;
	if (sig == SIGUSR1)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
		{
			write(1, "\n\033[32mEND OF TRANSMISSION\n", 25);
			ret = kill(info->si_pid, SIGUSR1);
			if (ret == -1)
				ft_putstr_fd("ERROR. KILL RETURN", 2);
			exit(0);
		}
		bit = 0;
		c = 0;
	}
}

/*
*	Using sigaction struct to specify an action on signal reception.
*	sa_sigaction point to function decode for signals processing.
*
*	Print the server process id to output for the client.
*	
*	sa_flags must be set with SA_SIGINFO so sigaction is gonna
*	be used. Otherwise sa_handler is used.
*/
int	main(int ac, char **av)
{
	int					ret;
	pid_t				process_id;
	struct sigaction	sig;

	if (ac != 1)
	{
		ft_putstr_fd("write: ", 2);
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	process_id = getpid();
	ft_putnbr_fd(process_id, 1);
	ft_putstr_fd("\n", 1);
	sig.sa_sigaction = decode;
	sig.sa_flags = SA_SIGINFO;
	ret = sigaction(SIGUSR1, &sig, NULL);
	if (ret == -1)
		ft_putstr_fd("SIGUSR1 ERROR.", 2);
	ret = sigaction(SIGUSR2, &sig, NULL);
	if (ret == -1)
		ft_putstr_fd("SIGUSR2 ERROR.", 2);
	while (1)
		;
}
