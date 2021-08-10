/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 10:46:25 by mmondell          #+#    #+#             */
/*   Updated: 2021/08/03 11:52:49 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (s != 0)
	{
		while (s[len])
			len++;
		write(fd, s, len);
	}
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		++str;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	else if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	return (result * sign);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n < 0 && n / 10 == 0)
	{
		c = '-';
		write(fd, &c, sizeof(char));
	}
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	if (n < 0)
	{
		c = (n % 10) * -1 + '0';
		write(fd, &c, sizeof(char));
	}
	else
	{
		c = n % 10 + '0';
		write(fd, &c, sizeof(char));
	}
}
