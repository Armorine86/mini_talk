/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_talk.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 10:20:14 by mmondell          #+#    #+#             */
/*   Updated: 2021/08/04 10:20:17 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TALK_H
# define MINI_TALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_atoi(const char *str);

#endif