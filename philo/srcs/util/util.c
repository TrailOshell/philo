/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:36:59 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/14 01:23:39 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	overflow_return(int nbr, int is_positive)
{
	if (nbr - 1 > 0)
		return (nbr * (is_positive));
	else if (is_positive == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	nbr;
	int	is_positive;

	nbr = 0;
	is_positive = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			is_positive = -1;
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + *str++ - '0';
		if (nbr < 0)
			return (overflow_return(nbr, is_positive));
	}
	return (nbr * (is_positive));
}

//	count the amount of digits in the number
int	digit_len(unsigned long number)
{
	int	len;

	if (number == 0)
		return (1);
	len = 0;
	while (number > 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}
